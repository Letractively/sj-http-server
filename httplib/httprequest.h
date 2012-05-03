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
    /**
     * @brief Method of the request, as defined in RFC 2616 sections 9.2 - 9.9
     */
    enum RequestMethod {OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT};

//public member functions
public:

    /**
     * @brief Reads data from socket and creates a request object
     *
     * It can handle 'usual' requests, as well as multipart requests with attached files
     *
     * @param socket tcp socket from which request data is to be read
     */
    HttpRequest(QTcpSocket * socket);


    /**
     * @brief Returns a relative URI of a resource
     *
     * The uri of a resourve starts with a '/' and does not contain protocol, host and port information.
     * Moreover, the full path of a resource is kept and any query string is ignored.
     * For example GET http://foo.bar/mypath/myresource?param1=2 produces uri of /mypath/myresource
     *
     * @return resource uri
     */
    QString getRequestUri() {return requestUri;}

    /**
     * @brief Returns a URL of a resource (as idicated by a client)
     *
     * The url of a resourve starts with protocol, then goes host and (optionally) port.
     * After that goes the resource uri. Any query string is ignored.
     * For example GET http://foo.bar/mypath/myresource?param1=2 produces uri of http://foo.bar/mypath/myresource
     *
     * @return resource url as indicated by the client
     */
    QString getRequestUrl() { return serverUrl + requestUri; }


    /**
     * @brief Returns the http method of the request
     * @return http mehod
     */
    RequestMethod getMethod() {return method;}

    /**
     * @brief Returns a request parameter
     * @param paramName name of the parameter
     * @return parameter value, or an aempty string if paramter is not defined in the request
     */
    QString getParameter(const QString & paramName) { return parameters.value(paramName); }

    /**
     * @brief Creates a string representation of a request. Used for debugging
     * @return request a string
     */
    QString toString();

    /**
     * @brief Returns value of an http header
     * @param headerName name of the header
     * @return header value or an empty string if header was not declared in the request
     */
    QString getHeaderValue(const QString & headerName);

    /**
     * @brief Returns all http headers
     * @return http headers declared in the request
     */
    QVector<HttpHeader> getHeaders() {return headers;}

    /**
     * @brief Returns lenght of the content
     * @return content length
     */
    quint64 getContentLength();

    void appendData(const QByteArray & data);
    QByteArray & getData();

    void addFile(HttpRequestBinaryFile binaryFile);
    void addParameter(QString paramName, QString paramValue);

    void setRelativePath(const QString & path) {this->relativePath = path;}
    QString getRelativePath() { return relativePath; }
    QVector<HttpRequestBinaryFile> & getBinaryFiles() { return binaryFiles; }


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
    QString serverUrl;
    QVector<HttpHeader> headers;
    QMap<QString, QString> parameters;
    QVector<HttpRequestBinaryFile> binaryFiles;
    quint64 contentLength;
    quint64 cachingThreshold;
    QByteArray requestData;
    QString relativePath;

};

#endif // HTTPREQUEST_H
