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


#include "handlermanager.h"
#include "requesthandler.h"
#include "serverutils.h"
#include "settingsconstants.h"
#include "configurationprovider.h"


#include <QPluginLoader>
#include <QStringList>

namespace SJ {

const Logger & HandlerManager::logger = LoggerFactory::instance().getLogger("sj-server-logger");

HandlerManager::HandlerManager()
{
    defaultHandler = HandlerData(new RequestHandler, HandlerConfiguration("DefualtRequetHandler", "Loads static contet", "", "", QMap<QString, QVariant>()));
    loadPluginsFromConfig();
}


void HandlerManager::loadPluginsFromConfig()
{
    QList<HandlerConfiguration> h = ConfigurationProvider::getInstance()->getHandlers();

    for(int i = 0; i < h.size(); ++i) {
        QPluginLoader pl(h[i].getFilePath());
        pl.load();
        LOG_DEBUG(logger, LogBuilder("Request handler loading from [").append(h[i].getFilePath()).append("]: ").append(pl.isLoaded() ? "success" : "failure"));
        AbstractRequestHandler * newHandler = 0;

        if(pl.isLoaded()) {
            newHandler = qobject_cast<AbstractRequestHandler *>(pl.instance());
        }

        if(newHandler != 0) {
            LOG_DEBUG(logger, LogBuilder("Created instance of the request handler ").append(newHandler->name()));
            handlers.push_back(HandlerData(newHandler, h[i]));
>>>>>>> d619c3d0715bf4bcbe7a6b2ac6245f9d811b92bd
        } else {
            LOG_DEBUG(logger, LogBuilder("Unable to load a handler: ").append(pl.errorString()));
        }

    }
}


HandlerManager::~HandlerManager()
{
    delete defaultHandler.getHandler();
    for(int i = 0; i < handlers.size(); ++i) {
        delete handlers[i].getHandler();
    }
}

HandlerManager & HandlerManager::instance()
{
    static HandlerManager mgr;
    return mgr;
}

HandlerData HandlerManager::getHandler(HttpRequest * request)
{
    QString uri = request->getRequestUri();

    QStringList list = uri.split("/", QString::SkipEmptyParts);

    if(!list.isEmpty()) {
        QString contextRoot = "/" + list[0];

        for(int i = 0; i < handlers.size(); ++i) {
            if(contextRoot == handlers[i].getContextRoot()) {
                list.removeAt(0);
                QString relativePath = "/" + list.join("/");
                return handlers[i];
            }
        }
    }

    return defaultHandler;
}

} // namespace SJ
