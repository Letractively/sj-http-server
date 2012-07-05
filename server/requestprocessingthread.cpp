/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include "requestprocessingthread.h"
#include "httpresponse.h"
#include "settingsconstants.h"
#include "abstractrequesthandler.h"
#include "handlermanager.h"
#include "serverutils.h"

#include <QFile>
#include <QImage>
#include <QSettings>
#include <QPluginLoader>
#include <QStringList>
#include <QHostAddress>

namespace SJ {

const Logger & RequestProcessingThread::logger = LoggerFactory::instance().getLogger("sj-req-proc-thread-logger");

RequestProcessingThread::RequestProcessingThread(int socketDescriptor, QObject * parent)
    :QThread(parent), socket(0), request(0), bytesRead(0),
      settings(Utils::getSettings())
{
    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, LogBuilder("Creating new RequestProcessingThread for socket descriptor [")
                  .append(socketDescriptor).append("]"));
    }

    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReadySlot()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(persistentConnTimeoutSlot()));

    if(logger.isTraceEnabled()) {
        LOG_TRACE(logger, LogBuilder("socket details: localAdress=").append(socket->localAddress().toString())
                  .append("; localPort=").append(socket->localPort()).append("; peerAddress=")
                  .append(socket->peerAddress().toString()).append("; peerPort=").append(socket->peerPort())
                  .append("; peerName=").append(socket->peerName()));
    }

}


void RequestProcessingThread::run()
{
    timer->start(30000);
    exec();
}

void RequestProcessingThread::dataReadySlot()
{
    if(request == 0) {
        request = new HttpRequestImpl(socket);
        if(logger.isTraceEnabled()) {
            LOG_TRACE(logger, LogBuilder("Creating new request object: [").append(request->toString()).append("]"));
        }
    }

    if(request->getMethod() == HttpRequest::GET) {
        processRequest();
    } else if (request->getMethod() == HttpRequest::POST) {
        preparePostRequest();
    }
}

void RequestProcessingThread::preparePostRequest() {
    QByteArray readData = socket->readAll();
    if(logger.isTraceEnabled()) {
        LOG_TRACE(logger, LogBuilder("reading data for POST request, read bytes: ").append(readData.length())
                  .append("Already read ").append(bytesRead).append(" out of ").append(request->getContentLength())
                  .append(" bytes"));
    }

    bytesRead += readData.length();

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
    } else if(contentType.startsWith("application/x-www-form-urlencoded")){
        parseFormParameters(request->getData());
    }

}

void RequestProcessingThread::parseFormParameters(const QByteArray & partData)
{
    QString dataString = QString(partData);
    QStringList paramsWithValues = dataString.split("&", QString::SkipEmptyParts);
    for(int i = 0; i < paramsWithValues.size(); ++i) {
        QStringList paramAndValue = paramsWithValues.at(i).split("=", QString::SkipEmptyParts);
        if(paramAndValue.size() > 0 && paramAndValue.at(0).length() > 0) {
            if(paramAndValue.size() == 1) {
                request->addParameter(paramAndValue.at(0), "");
            } else {
                request->addParameter(paramAndValue.at(0), paramAndValue.at(1));
            }
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


void RequestProcessingThread::processRequest() {
    HandlerData handlerData = HandlerManager::instance().getHandler(request);
    AbstractRequestHandler * handler = handlerData.getHandler();
    LOG_TRACE(logger, LogBuilder("Processing request with ").append(handler->name()));
    QSettings::SettingsMap * sets = readHandlerSettings(handlerData.getSettingsGroup());
    HttpResponse response = handler->handle(request, sets);
    delete sets;
    response.writeToSocket(socket);
    delete request;
    request = 0;
}

QSettings::SettingsMap * RequestProcessingThread::readHandlerSettings(const QString & handlerSettingsKey)
{

    QSettings::SettingsMap * map = new QSettings::SettingsMap;
    if("" == handlerSettingsKey) {
        return map;
    }

    QStringList keys = settings.allKeys();

    for(int i = 0; i < keys.length(); ++i) {
        if(keys.at(i).startsWith(handlerSettingsKey + "/")) {
            map->insert(Utils::substring(keys.at(i), handlerSettingsKey.length() + 1), settings.value(keys.at(i)));
        }
    }

    return map;
}

void RequestProcessingThread::persistentConnTimeoutSlot()
{
    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, LogBuilder("Persistent connection timed out for socket descriptor ")
                  .append(socket->socketDescriptor()));
    }
    socket->disconnectFromHost();
}

void RequestProcessingThread::disconnectedSlot()
{
    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, LogBuilder("Disconnecting socket with socket descriptor ")
                  .append(socket->socketDescriptor()));
    }
    disconnect(this);
    this->quit();
}

void RequestProcessingThread::serverStoppedSlot()
{
    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, LogBuilder("Server stopped, disconnecting socket with descriptor ")
                  .append(socket->socketDescriptor()));
    }
    socket->disconnectFromHost();
}

} //namespace SJ
