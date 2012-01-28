/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Samir Jorina

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


#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QByteArray>
#include <QTcpSocket>
#include <QStringList>
#include <QVector>
#include <QMap>

#include "httpheader.h"
#include "httprequestbinaryfile.h"

class HttpRequest
{
//piblic types
public:
    enum RequestMethod {ERROR, GET, POST};

//public member functions
public:
    HttpRequest(QTcpSocket * socket);
    QString getRequestUri() {return requestUri;}
    RequestMethod getMethod() {return method;}
    bool isMultipart() {return multipart; }
    QString toString();

    QString getHeaderValue(const QString & headerName);

    QVector<HttpHeader> getHeaders() {return headers;}

    quint64 getContentLength();

    void appendData(const QByteArray & data);
    QByteArray & getData();

    void addFile(HttpRequestBinaryFile binaryFile);
    void addParameter(QString paramName, QString paramValue);

//private member functions
private:
    void setUpMethodAndLocation(const QString & methodLine);
    void setUpHeaders(const QStringList & tokensList);
    void setUpParameters(const QString & locationLine);
    QString methodToString();
    QString headersToString();
    QString parametersToString();

    void parseData(QByteArray & data);
    void parsePart(const QByteArray & part);


//private fields
private:
    RequestMethod method;
    QString requestUri;
    QVector<HttpHeader> headers;
    QMap<QString, QString> parameters;
    QVector<HttpRequestBinaryFile> binaryFiles;
    bool multipart;
    quint64 contentLength;
    quint64 cachingThreshold;
    QByteArray requestData;

};

#endif // HTTPREQUEST_H
