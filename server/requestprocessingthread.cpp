/*
http://sj-http-server.googlecode.com/

Copyright (C) Jakub Wachowski

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
#include "httpresponseimpl.h"
#include "abstractrequesthandler.h"
#include "handlermanager.h"
#include "serverutils.h"

#include <QFile>
#include <QPluginLoader>
#include <QStringList>
#include <QHostAddress>

namespace SJ {

const Logger & RequestProcessingThread::logger = LoggerFactory::instance().getLogger("sj-req-proc-thread-logger");

RequestProcessingThread::RequestProcessingThread(int socketDescriptor, QObject * parent)
    :QThread(parent), socket(0), request(0), bytesRead(0)
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

    if(request->getContentLength() == 0) {
        processRequest();
    } else {
        prepareRequest();
    }
}

void RequestProcessingThread::prepareRequest() {

    QByteArray readData = socket->readAll();
    if(readData.length() == 0 && request->getHeaderValue("Expect") == "100-continue") {
        HttpResponseImpl::writeContinue(socket);
        //there is no data yet
        return;
    }

    if(logger.isTraceEnabled()) {
        LOG_TRACE(logger, LogBuilder("reading data for request, read bytes: ").append(readData.length())
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
    if(partData.contains(HttpHeader::CONTENT_TYPE.toUtf8())) {

        QString originalFileName = findAttributeValue("filename", partData);
        QString contentType = findHeaderValue(HttpHeader::CONTENT_TYPE, partData);
        QByteArray data = findData(partData);

        if(data.isEmpty()) {
            //no file was uploaded
            return;
        }

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
    const Logger & httpLogger = LoggerFactory::instance().getLogger("sj-http-dump-logger");
    if(httpLogger.isDebugEnabled()) {
        LogBuilder lb;
        lb.append("REQUEST ID [").append(request->getRequestID()).append("]\n");
        lb.append(request->toString());
        lb.append("\n");
        LOG_DEBUG(httpLogger, lb.toString());
    }
    HttpResponseImpl * response = new HttpResponseImpl(request->getRequestID());

    switch(request->getMethod()) {
        case HttpRequest::RequestMethod::GET:
            handler->handleGet(request, response);
            break;
    case HttpRequest::RequestMethod::POST:
        handler->handlePost(request, response);
        break;
    case HttpRequest::RequestMethod::PUT:
        handler->handlePut(request, response);
        break;
    case HttpRequest::RequestMethod::DELETE:
        handler->handleDelete(request, response);
        break;
    default:
        response->setStatusCode(HttpResponse::StatusCode::SC_BAD_REQUEST);
        break;
    }

    response->writeToSocket(socket);
    delete response;
    delete request;
    request = 0;
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
        LOG_DEBUG(logger, LogBuilder("Socket diconnected"));
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
