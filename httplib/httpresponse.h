/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011  Samir Jorina

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QString>
#include <QVector>
#include <QByteArray>
#include <QTcpSocket>
#include <QFile>

#include "httpheader.h"

class HttpResponse
{
public:

    enum StatusCode {OK = 200, NOT_FOUND = 404};

    HttpResponse();
    HttpResponse(StatusCode code);
    HttpResponse(QByteArray * data, QString contentType = "text/html");
    HttpResponse(QString filePath, QString contentType = "");
    ~HttpResponse();

    void setStatusCode(StatusCode code);
    void addHeader(QString name, QString value);
    void writeToSocket(QTcpSocket * socket);

private:
    static const char * EOL;
    static QString codeToString(StatusCode code);
    static QString guessContentType(QString filePath);
    void setDefaultHeaders();

    StatusCode code;
    QVector<HttpHeader> headers;
    QByteArray data;
    QFile * file;
};

#endif // HTTPRESPONSE_H
