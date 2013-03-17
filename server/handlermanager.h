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


#ifndef HANDLERMANAGER_H
#define HANDLERMANAGER_H

#include "abstractrequesthandler.h"
#include "handlerdata.h"
#include "loggerall.h"

#include <QVector>

namespace SJ {

class HandlerManager
{
public:

    HandlerManager();

    ~HandlerManager();

    static HandlerManager & instance();

    HandlerData getHandler(HttpRequest * request);

    /**
     * @return Name of the handler (as returned by the plugin)
     */

    QVector<HandlerData> * getAllHandlers() { return &handlers; }

private:

    void loadPluginsFromConfig();

    AbstractRequestHandler * loadPlugin(const QString & filepath, const QString & settingsKey);



    HandlerData defaultHandler;
    QVector<HandlerData> handlers;

    static const Logger & logger;
};

} // namespace SJ

#endif // HANDLERMANAGER_H
