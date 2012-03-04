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


#ifndef ABSTRACTREQUESTHANDLER_H
#define ABSTRACTREQUESTHANDLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "settingsitem.h"

#include <QVector>
#include <QSettings>
#include <QtPlugin>

class AbstractRequestHandler
{
public:
    virtual ~AbstractRequestHandler() {}
    /**
     * @brief returns name of the handler
     */
    virtual QString name() const = 0;
    virtual QString description() const { return ""; }
    virtual QString helpInfo() const { return ""; }
    virtual HttpResponse handle(HttpRequest * req, QSettings::SettingsMap * settings = 0) const = 0;
    virtual QVector<SettingsItem> supportedSettings() const { return QVector<SettingsItem>(0); }
};

Q_DECLARE_INTERFACE(AbstractRequestHandler, "sj.http.server.AbstractRequestHandler/0.1")

#endif // ABSTRACTREQUESTHANDLER_H
