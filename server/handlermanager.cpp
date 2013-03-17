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


#include "handlermanager.h"
#include "requesthandler.h"
#include "serverutils.h"
#include "settingsconstants.h"


#include <QPluginLoader>
#include <QStringList>

namespace SJ {

const Logger & HandlerManager::logger = LoggerFactory::instance().getLogger("sj-server-logger");

HandlerManager::HandlerManager()
{
    defaultHandler = HandlerData(new RequestHandler, "DefaultRequestHandler");
    loadPluginsFromConfig();
}


void HandlerManager::loadPluginsFromConfig()
{
    QSettings & settings = Utils::getSettings();

    int size = settings.beginReadArray(PluginSettings::PLUGIN_GROUP_NAME);

    for(int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        loadPlugin(settings.value(PluginSettings::PLUGIN_FILE_PATH).toString(), settings.value(PluginSettings::PLUGIN_SETTINGS_KEY).toString());
    }

    settings.endArray();
}


AbstractRequestHandler * HandlerManager::loadPlugin(const QString & filepath, const QString & settingsKey)
{
    QPluginLoader pl(filepath);
    pl.load();
    LOG_DEBUG(logger, LogBuilder("Request handler loading from [").append(filepath).append("]: ").append(pl.isLoaded() ? "success" : "failure"));

    AbstractRequestHandler * newHandler = 0;

    if(pl.isLoaded()) {
        newHandler = qobject_cast<AbstractRequestHandler *>(pl.instance());
    }

    if(newHandler != 0) {
        LOG_DEBUG(logger, LogBuilder("Created instance of the request handler ").append(newHandler->name()));
        handlers.push_back(HandlerData(newHandler, settingsKey));
    } else {
        LOG_DEBUG(logger, LogBuilder("Unable to load a handler: ").append(pl.errorString()));
    }

    return newHandler;
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
