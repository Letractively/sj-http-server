/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include "requestprocessingthread.h"
#include "httpresponse.h"
#include "settingsconstants.h"
#include "logger.h"
#include "abstractrequesthandler.h"
#include "handlermanager.h"
#include "serverutils.h"

#include <QFile>
#include <QImage>
#include <QDebug>
#include <QSettings>
#include <QPluginLoader>

RequestProcessingThread::RequestProcessingThread(int socketDescriptor, QObject * parent)
    :QThread(parent), socket(0), request(0), bytesRead(0),
      settings(Utils::getSettings())
{
    qDebug() << "thread created";
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReadySlot()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}


void RequestProcessingThread::run()
{
    exec();
}

void RequestProcessingThread::dataReadySlot()
{
    if(request == 0) {
        request = new HttpRequest(socket);
        qDebug() << request->toString();
    }

    if(request->getMethod() == HttpRequest::GET) {
        processRequest();
    } else if (request->getMethod() == HttpRequest::POST) {
        preparePostRequest();
    }
}

void RequestProcessingThread::preparePostRequest() {
    qDebug() << "processing POST Request";
    QByteArray readData = socket->readAll();
    qDebug() << "Read " << readData.length() << " bytes";

    bytesRead += readData.length();

    qDebug() << "Read " << bytesRead << " of " << request->getContentLength() << " bytes";

    if(readData.length() > 0) {
        request->appendData(readData);
    }

    if(bytesRead >= request->getContentLength() || readData.length() == 0) {
        parseRequest();
        processRequest();

    }
}

void RequestProcessingThread::parseRequest() {

    QString contentType = HttpHeader::getHeaderValue(HttpHeader::CONTENT_TYPE, request->getHeaders());
    QByteArray & partsData = request->getData();

    if(contentType.startsWith("multipart/form-data")) {
        QString boundary = "--" + contentType.right(contentType.length() - contentType.indexOf("boundary=") - 9);
        int boundaryLength = boundary.length();

        int pos = partsData.indexOf(boundary);
        while(pos >= 0) {
            int prevPos = pos;
            pos = partsData.indexOf(boundary, prevPos + 1);
            if(pos < 0) {
                break;
            }

            parsePart(partsData.mid(prevPos + boundaryLength, pos - prevPos - boundaryLength));
        }
    }
}

QString RequestProcessingThread::findHeaderValue(const QString & headerName, const QByteArray & data)
{
    int pos = data.indexOf(headerName);
    int pos2 = data.indexOf('\n', pos + 1);
    return QString(data.mid(pos + headerName.length() + 1, pos2 - pos - headerName.length() - 1)).trimmed();
}

QByteArray RequestProcessingThread::findData(const QByteArray & data) {
    int pos = data.indexOf("\r\n\r\n");

    QByteArray a = data.mid(pos + 4);
    a  = a.left(a.length() - 2);
    return a;
}

void RequestProcessingThread::parsePart(const QByteArray & partData) {
    if(partData.contains(HttpHeader::CONTENT_TYPE.toAscii())) {

        QString originalFileName = findAttributeValue("filename", partData);
        QString contentType = findHeaderValue(HttpHeader::CONTENT_TYPE, partData);
        QByteArray data = findData(partData);

        HttpRequestBinaryFile  binaryFile(data, originalFileName, contentType);
        request->addFile(binaryFile);

    } else {
        //parameters
        QString paramName = findAttributeValue("name", partData);
        QString paramValue = QString(findData(partData)).trimmed();
        request->addParameter(paramName, paramValue);
    }

}

QString RequestProcessingThread::findAttributeValue(const QString & attributeName, const QByteArray & partData) {

    int attributeNameLength = attributeName.length() + 2;
    int paramBegin = partData.indexOf(attributeName + "=\"");
    int paramEnd = partData.indexOf("\"", paramBegin + attributeNameLength);
    return QString(partData.mid(paramBegin + attributeNameLength, paramEnd - paramBegin - attributeNameLength));

}

//void RequestProcessingThread::saveBinaryFile(HttpRequestBinaryFile * fileToSave)
//{
//    QString storePath = settings.value(SETTING_FILE_STORE_PATH).toString();
//    QString filePath = storePath + fileToSave->getFileName();
//    QFile file(filePath);
//    file.open(QFile::WriteOnly);
//    file.write(fileToSave->getData());
//    file.flush();
//    file.close();

//    qDebug() << "file saved to " << filePath;
//    Logger::instance().debug("File saved to " + filePath);

//    bool miniatureEnabled = settings.value(SETTING_MINIATURE_ENABLED).toBool();

//    if(miniatureEnabled) {
//        QImage image(filePath);

//        int miniatureSize = settings.value(SETTING_MINIATURE_SIZE).toInt();

//        if(image.width() > image.height()) {
//            image = image.scaledToWidth(miniatureSize);
//        } else {
//            image = image.scaledToHeight(miniatureSize);
//        }
//        filePath = storePath +"s" + fileToSave->getFileName();
//        image.save(filePath);
//        qDebug() << "miniature saved to" << filePath;
//        Logger::instance().debug("Miniature saved to " + filePath);
//    }

//}

void RequestProcessingThread::processRequest() {
    qDebug() << "processing GET Request: " << request->getRequestUri();

    AbstractRequestHandler * handler = HandlerManager::instance().getHandler(request);
    qDebug() << "Processing request with" << handler->name();
    HttpResponse response = handler->handle(request, &settings);
    response.writeToSocket(socket);
    delete request;
    request = 0;
}


void RequestProcessingThread::disconnectedSlot()
{
    qDebug() << "   SOCKET SIGNAL disconnected";
    disconnect(this);
    this->quit();
}

void RequestProcessingThread::serverStoppedSlot()
{
    qDebug() << "Server stopped, disconnecting from socket";
    socket->disconnectFromHost();
}
