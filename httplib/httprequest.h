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


#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "httpheader.h"
#include "httprequestbinaryfile.h"

#include <QVector>

namespace SJ {

/**
 * @brief Abstract class representing an http request
 */
class HttpRequest
{

public:

    HttpRequest() {}
    virtual ~HttpRequest() {}

    /**
     * @brief Method of the request, as defined in RFC 2616 sections 9.2 - 9.9
     */
    enum class RequestMethod {OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT};

    /**
     * @brief Returns a relative URI of a resource
     *
     * The uri of a resourve starts with a '/' and does not contain protocol, host and port information.
     * Moreover, the full path of a resource is kept and any query string is ignored.
     * For example GET http://foo.bar/mypath/myresource?param1=2 produces uri of /mypath/myresource
     *
     * @return resource uri
     */
    virtual QString getRequestUri() const = 0;

    /**
     * @brief Returns a URL of a resource (as idicated by a client)
     *
     * The url of a resourve starts with protocol, then goes host and (optionally) port.
     * After that goes the resource uri. Any query string is ignored.
     * For example GET http://foo.bar/mypath/myresource?param1=2 produces uri of http://foo.bar/mypath/myresource
     *
     * @return resource url as indicated by the client
     */
    virtual QString getRequestUrl() const = 0;


    /**
     * @brief Returns the http method of the request
     * @return http mehod
     */
    virtual RequestMethod getMethod() const = 0;

    /**
     * @brief Returns a request parameter
     * @param paramName name of the parameter
     * @return parameter value, or an aempty string if paramter is not defined in the request
     */
    virtual QString getParameter(const QString & paramName) const = 0;


    /**
     * @brief Returns value of an http header
     * @param headerName name of the header
     * @return header value or an empty string if header was not declared in the request
     */
    virtual QString getHeaderValue(const QString & headerName) const = 0;

    /**
     * @brief Returns all http headers
     * @return http headers declared in the request
     */
    virtual QVector<HttpHeader> getHeaders() const = 0;

    /**
     * @brief Returns a set of files that have been uploaded
     * @return uploaded files
     */
    virtual QVector<HttpRequestBinaryFile> getBinaryFiles() const = 0;

};

} //namespace SJ
#endif // HTTPREQUEST_H
