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


#include "httpresponseimpl.h"
#include "httpheader.h"
#include "serverutils.h"
#include <QDebug>


namespace SJ {

const char * HttpResponseImpl::EOL = "\r\n";
const Logger &  HttpResponseImpl::logger = LoggerFactory::instance().getLogger("sj-http-dump-logger");

HttpResponseImpl::HttpResponseImpl(const QString &requestID)
    : code(SC_OK), file(0), contentType(""), requestID(requestID)
{
    setDefaultHeaders();
}


void HttpResponseImpl::fromFile(const QString & filePath)
{
    qDebug() << "file " << filePath;

    file = new QFile(filePath);
    if(!file->exists()) {
        code = SC_NOT_FOUND;
        delete file;
        file = 0;
        return;
    }

    if(contentType == "") {
        //guess content type
        this->contentType = guessContentType(filePath);
    }

}

HttpResponseImpl::~HttpResponseImpl()
{
}

void HttpResponseImpl::setStatusCode(StatusCode code)
{
    this->code = code;
}

void HttpResponseImpl::addHeader(QString name, QString value)
{
    //TODO: now empty headers are silently ignored -add some way signalizing an error
    if(! name.isEmpty() && ! value.isEmpty()) {
        headers.push_back(HttpHeader(name, value));
    }
}

void HttpResponseImpl::writeData(const QByteArray & data)
{
    this->data.append(data);
}

void HttpResponseImpl::setContentType(const QString & contentType)
{
    this->contentType = contentType;
}

void HttpResponseImpl::writeToSocket(QTcpSocket * socket)
{
    if(code == SC_NOT_FOUND) {
        socket->write(("HTTP/1.1 " + codeToString(this->code) + EOL).toStdString().c_str());
        socket->write("ContentType: text/plain");
        socket->write(EOL);
        socket->write("Connection: close");
        socket->write(EOL);
        socket->write(EOL);
        socket->write("Resource not found");
        socket->disconnectFromHost();
        return;
    }

    addHeader(HttpHeader::CONTENT_TYPE, contentType);

    qlonglong contentLength = data.size();

    if(file != 0) {
        contentLength += file->size();
    }

    QString val;
    val.setNum(contentLength);

    addHeader(HttpHeader::CONTENT_LENGTH, val);

    socket->write(("HTTP/1.1 " + codeToString(this->code) + EOL).toStdString().c_str());

    LogBuilder lb;

    if(logger.isDebugEnabled()) {
        lb.append("RESPONSE ID [").append(requestID).append("]").append("\n");
        lb.append("HTTP/1.1 ").append(codeToString(this->code)).append("\n");
    }

    for(int i = 0; i < headers.size(); ++i) {
        socket->write((headers[i].toString() + EOL).toStdString().c_str());
        if(logger.isDebugEnabled()) {
            lb.append(headers[i].toString()).append("\n");
        }
    }
    socket->write(EOL);
    if(logger.isDebugEnabled()) {
        lb.append("\n");
    }


    if(data.size() > 0) {
        socket->write(data);
        if(logger.isTraceEnabled()) {
            lb.append(data);
        }
    }

    if(file != 0 && file->size() > 0) {
        file->open(QFile::ReadOnly);
        const qint64 MAX_SIZE = 256000;

        while(true) {
            QByteArray d = file->read(MAX_SIZE);
            if(d.size() > 0) {
                socket->write(d);
                if(logger.isTraceEnabled()) {
                    lb.append(d);
                }
            } else {
                break;
            }
        }

        file->close();
        delete file;
    }

    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, lb.toString());
    }
}

QString HttpResponseImpl::codeToString(StatusCode code)
{
    switch(code) {
    case SC_CONTINUE: return "100 Continue";
    case SC_SWITCHING_PROTOCOL: return "101 Switching Protocol";
    case SC_OK: return "200 OK";
    case SC_CREATED: return "201 Created";
    case SC_ACCEPTED: return "202 Accepted";
    case SC_NON_AUTHORITATIVE_INFORMATION: return "203 Authoritative Information";
    case SC_NO_CONTENT: return "204 No Content";
    case SC_RESET_CONTENT: return "205 Reset Content";
    case SC_PARTIAL_CONTENT: return "206 Partial Content";
    case SC_MULTIPLE_CHOICES: return "300 Multiple Choices";
    case SC_MOVED_PERMANENTLY: return "301 Moved Permanently";
    case SC_FOUND: return "302 Found";
    case SC_SEE_OTHER: return "303 See Other";
    case SC_NOT_MODIFIED: return "304 Not Modified";
    case SC_USE_PROXY: return "305 Use Proxy";
    case SC_TEMPORARY_REDIRECT: return "307 Temporary Redirect";
    case SC_BAD_REQUEST: return "400 Bad Request";
    case SC_UNAUTHORIZED: return "401 Unauthorized";
    case SC_FORBIDDEN: return "403 Forbidden";
    case SC_NOT_FOUND: return "404 Not Found";
    case SC_METHOD_NOT_ALLOWED: return "405 Method Not Allowed";
    case SC_NOT_ACCEPTABLE: return "406 Not Acceptable";
    case SC_PROXY_AUTHENTICATION_REQUIRED: return "407 Proxy Authentication Required";
    case SC_REQUEST_TIMEOUT: return "408 Request Timeout";
    case SC_CONFLICT: return "409 Conflict";
    case SC_GONE: return "410 GONE";
    case SC_LENGTH_REQUIRED: return "411 Length Required";
    case SC_PRECONDITION_FAILED: return "412 Precondition Failed";
    case SC_REQUEST_ENTITY_TOO_LARGE: return "413 Request Entity Too Large";
    case SC_REQUEST_URI_TOO_LONG: return "414 Request Uri Too Large";
    case SC_UNSUPPORTED_MEDIA_TYPE: return "415 Unsupported Media Type";
    case SC_REQUESTED_RANGE_NOT_SATISFIABLE: return "416 Requested Range Not Satisfiable";
    case SC_EXPECTATION_FAILED: return "417 Expectation Failed";
    case SC_INTERNAL_SERVER_ERROR: return "500 Internal Server Error";
    case SC_NOT_IMPLEMENTED: return "501 Not Implemented";
    case SC_BAD_GATEWAY: return "502 Bad Gateway";
    case SC_SERVICE_UNAVAILABLE: return "503 Service Unavailable";
    case SC_GATEWAY_TIMEOUT: return "504 Gateway Timeout";
    case SC_HTTP_VERSION_NOT_SUPPORTED: return "505 HTTP Version Not Supported";
    }
    return "";
}

void HttpResponseImpl::setDefaultHeaders()
{
//    addHeader("Connection", "close");
    addHeader("Connection", "Keep-Alive");
    addHeader("Server", "SJ-Server v. " + Utils::version());
}


QString HttpResponseImpl::guessContentType(QString filePath)
{
    QString filePathLower = filePath.toLower();

    if(filePathLower.endsWith(".html") || filePathLower.endsWith(".htm")) {
        return "text/html";
    }

    if(filePathLower.endsWith(".txt")) {
        return "image/plain";
    }

    if(filePathLower.endsWith(".png")) {
        return "image/png";
    }

    if(filePathLower.endsWith(".jpg") || filePathLower.endsWith(".jpeg")) {
        return "image/jpeg";
    }

    if(filePathLower.endsWith(".gif")) {
        return "image/gif";
    }

    if(filePathLower.endsWith(".tiff")) {
        return "image/tiff";
    }

    if(filePathLower.endsWith(".pdf")) {
        return "application/pdf";
    }

    if(filePathLower.endsWith(".mp4")) {
        return "video/mp4";
    }


    if(filePathLower.endsWith(".ico")) {
        return "image/x-icon";
    }

    return "";
}

} //namespace SJ
