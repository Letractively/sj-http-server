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


#include "httpresponse.h"
#include "serverutils.h"

const char * HttpResponse::EOL = "\r\n";


HttpResponse::HttpResponse()
    : code(OK), file(0)
{
    setDefaultHeaders();
}

HttpResponse::HttpResponse(StatusCode code)
    :code(code), file(0)
{
    setDefaultHeaders();
}

HttpResponse::HttpResponse(QByteArray * data, QString contentType)
    : code(OK), data(*data), file(0)
{
    setDefaultHeaders();
    addHeader(HttpHeader::CONTENT_TYPE, contentType);
}

HttpResponse::HttpResponse(QString filePath, QString contentType)
    :code(OK), file(0)
{
    setDefaultHeaders();
    qDebug() << "producing response from file " << filePath;
    file = new QFile(filePath);
    if(!file->exists()) {
        code = NOT_FOUND;
        delete file;
        file = 0;
        return;
    }

    qDebug() << "file size " << file->size();

    if(contentType != "") {
        addHeader(HttpHeader::CONTENT_TYPE, contentType);
    } else {
        //guess content type
        QString type = guessContentType(filePath);
        //add header only if known type - otherwise client will try to guess the type
        if("" != type) {
            addHeader(HttpHeader::CONTENT_TYPE, type);
        }
    }

}

HttpResponse::~HttpResponse()
{
}

void HttpResponse::setStatusCode(StatusCode code)
{
    this->code = code;
}

void HttpResponse::addHeader(QString name, QString value)
{
    //TODO: now empty headers are silently ignored -add some way signalizing an error
    if(! name.isEmpty() && ! value.isEmpty()) {
        headers.push_back(HttpHeader(name, value));
    }
}

void HttpResponse::writeToSocket(QTcpSocket * socket)
{
    if(code == NOT_FOUND) {
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
    qlonglong contentLength = data.size();

    if(file != 0) {
        contentLength += file->size();
    }

    QString val;
    val.setNum(contentLength);

    addHeader(HttpHeader::CONTENT_LENGTH, val);

    socket->write(("HTTP/1.1 " + codeToString(this->code) + EOL).toStdString().c_str());


    qDebug() << "Returning response ";
    qDebug() << "HTTP/1. " + codeToString(this->code);

    for(int i = 0; i < headers.size(); ++i) {
        socket->write((headers[i].toString() + EOL).toStdString().c_str());
        qDebug() << headers[i].toString();
    }
    socket->write(EOL);
    qDebug() << "";


    if(data.size() > 0) {
        qDebug() << data;
        socket->write(data);
    }

    if(file != 0 && file->size() > 0) {
        file->open(QFile::ReadOnly);
        const qint64 MAX_SIZE = 256000;

        while(true) {
            QByteArray d = file->read(MAX_SIZE);
            if(d.size() > 0) {
                qDebug() << d;
                socket->write(d);
            } else {
                break;
            }
        }

        file->close();
        delete file;
    }
}

QString HttpResponse::codeToString(StatusCode code)
{
    switch(code) {
    case OK: return "200 OK";
    case NOT_FOUND: return "404 Not Found";
    }
    return "500 Internal Server Error";
}

void HttpResponse::setDefaultHeaders()
{
//    addHeader("Connection", "close");
    addHeader("Connection", "Keep-Alive");
    addHeader("Server", "SJ-Server v. " + Utils::version());
}


QString HttpResponse::guessContentType(QString filePath)
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


