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


#ifndef ABSTRACTREQUESTHANDLER_H
#define ABSTRACTREQUESTHANDLER_H

#include "httprequest.h"
#include "httpresponse.h"

#include <QMap>
#include <QVariant>
#include <QtPlugin>

namespace SJ {

/**
 * @brief Class represents a request handler, i.e. a plugin that can process an http request
 *  and produce an http response
 *
 * This abstract class needs to be inherited by all the plugins. All its member functions are virtual.
 */
class AbstractRequestHandler
{
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~AbstractRequestHandler() {}

    /**
     * @brief Initializes the handler with defined parameters.
     *
     * This is the entry point for each loaded handler and is called only once - on load. If not overridden,
     * this function does nothing.
     *
     * @param initParams map of parameters.
     */
    virtual void init(const QMap<QString, QVariant> & initParams);


    virtual void handleGet(HttpRequest * request, HttpResponse * response) const;
    virtual void handlePost(HttpRequest * request, HttpResponse * response) const;
    virtual void handlePut(HttpRequest * request, HttpResponse * response) const;
    virtual void handleDelete(HttpRequest * request, HttpResponse * response) const;


    /**
     * @brief Returns name of the handler
     *
     * Name will be presented to the user in the server GUI, thus it should identify the handler.
     * This function is purly virtual and must be implemented in derived classes.
     *
     * @return handler's name
     */
    virtual QString name() const = 0;

private:
    void internalHandle(HttpResponse * response) const;
};

} //namespace SJ

Q_DECLARE_INTERFACE(SJ::AbstractRequestHandler, "sj.http.server.AbstractRequestHandler/0.1")

#endif // ABSTRACTREQUESTHANDLER_H
