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


#ifndef ABSTRACTREQUESTHANDLER_H
#define ABSTRACTREQUESTHANDLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "settingsitem.h"

#include <QVector>
#include <QSettings>
#include <QtPlugin>


/**
 * @brief Class represents a request handler, i.e. a plugin that can process an http request
 *  and produce an http response
 *
 * This abstract class needs to be inherited by all the plugins. All its member functions are virtual.
 */
class AbstractRequestHandler
{
public:
    virtual ~AbstractRequestHandler() {}
    /**
     * @brief Returns name of the handler
     *
     * Name will be presented to the user in the server GUI, thus it should identify the handler.
     * This function is purly virtual and must be implemented in derived classes.
     *
     * @return handler's name
     */
    virtual QString name() const = 0;

    /**
     * @brief Returns a description of the handler.
     *
     * The description should explain what the plugin does, The description should be kept short.
     * Returns empty string if not overridden in a derived class
     *
     * @return handler's description
     */
    virtual QString description() const { return ""; }

    /**
     * @brief Help information about the hamdler
     *
     * It should contain a detailed description of the handler and possibly also the settings accepted by the handler.
     * It is to be presented in the help windows. Can be richtext.
     * Returns empty string if not overridden in a derived class
     *
     * @return handler's help information
     */
    virtual QString helpInfo() const { return ""; }

    /**
     * @brief Process an http request and produces a response
     *
     * This is the entry point for each request. Handler receives the request and set of configuration entries
     * (those configured for this handler) and is supposed to return a http response. This is purly virtual function
     * and needs to be overriden by derived classes.
     *
     * @param request http request for which response should be returned
     * @param settings configuration of the handler
     * @return response to the request
     */
    virtual HttpResponse handle(HttpRequest * request, QSettings::SettingsMap * settings = 0) const = 0;

    /**
     * @brief return which settings are supported by the handler
     *
     * These settings are used when creating a configuration dialog for the handler.
     * If not overridden, this function returns empty vector (no settings supported).
     *
     * @return vector containing supported settings
     */
    virtual QVector<SettingsItem> supportedSettings() const { return QVector<SettingsItem>(0); }
};

Q_DECLARE_INTERFACE(AbstractRequestHandler, "sj.http.server.AbstractRequestHandler/0.1")

#endif // ABSTRACTREQUESTHANDLER_H
