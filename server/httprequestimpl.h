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


#ifndef HTTPREQUESTIMPL_H
#define HTTPREQUESTIMPL_H


#include "httpheader.h"
#include "httprequest.h"
#include "httprequestbinaryfile.h"

#include <QTcpSocket>
#include <QByteArray>
#include <QStringList>
#include <QMap>
#include <QVector>

namespace SJ {

class HttpRequestImpl : public HttpRequest
{
public:

    /**
     * @brief Reads data from socket and creates a request object
     *
     * It can handle 'usual' requests, as well as multipart requests with attached files
     *
     * @param socket tcp socket from which request data is to be read
     */
    HttpRequestImpl(QTcpSocket * socket);


    /*
     * Implementation of virtual methods from HttpRequest
     */
    virtual QString getRequestUri() const;
    virtual QString getRequestUrl() const;
    virtual RequestMethod getMethod() const;
    virtual QString getParameter(const QString & paramName) const;
    virtual QString getHeaderValue(const QString & headerName) const;
    virtual QVector<HttpHeader> getHeaders() const;
    virtual QVector<HttpRequestBinaryFile> getBinaryFiles() const;



    /**
     * @brief Returns length of the content
     * @return content length
     */
    quint64 getContentLength();

    void appendData(const QByteArray & data);
    QByteArray & getData();

    void addFile(HttpRequestBinaryFile binaryFile);
    void addParameter(QString paramName, QString paramValue);



    /**
     * @brief Creates a string representation of a request. Used for debugging
     * @return request a string
     */
    QString toString();



protected:
    /**
     * @brief empty constructor
     */
    HttpRequestImpl();


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
    quint64 contentLength;
    RequestMethod method;
    mutable QString requestUri;
    mutable QString requestUrl;
    QString location;
    QVector<HttpHeader> headers;
    QMap<QString, QString> parameters;
    QVector<HttpRequestBinaryFile> binaryFiles;
    quint64 cachingThreshold;
    QByteArray requestData;


};
} //namespace SJ

#endif // HTTPREQUESTIMPL_H
