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


#include "handlermanager.h"
#include "requesthandler.h"
#include "serverutils.h"
#include "settingsconstants.h"

#include <QPluginLoader>
#include <QStringList>


HandlerManager::HandlerManager()
{
    defaultHandler = HandlerData(new RequestHandler, "DefaultRequestHandler");
    loadPluginsFromConfig();
}


//QString HandlerManager::registerHandler(const QString & filePath, const QString & settingsKey)
//{
//    AbstractRequestHandler * newHandler = loadPlugin(filePath, settingsKey);

//    if(0 != newHandler) {
//        persistHandlerConfig(filePath, contextRoot);

//        return newHandler->name();
//    }

//    return "";
//}


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

//void HandlerManager::persistHandlerConfig(const QString & filepath)
//{
//    QSettings & settings = Utils::getSettings();

//    int size = settings.beginReadArray(PluginSettings::PLUGIN_GROUP_NAME);
//    settings.endArray();

//    settings.beginWriteArray(PluginSettings::PLUGIN_GROUP_NAME);
//    settings.setArrayIndex(size);
//    settings.setValue(PluginSettings::PLUGIN_FILE_PATH, filepath);
//    settings.setValue(PluginSettings::PLUGIN_CONTEXT_ROOT, contextRoot);
//    settings.endArray();
//    settings.sync();
//}

AbstractRequestHandler * HandlerManager::loadPlugin(const QString & filepath, const QString & settingsKey)
{
    AbstractRequestHandler * newHandler = 0;
    QPluginLoader pl(filepath);
    pl.load();
    qDebug() << "new handler loaded " << pl.isLoaded();
    if(pl.isLoaded()) {
        qDebug() << "creating instance ...";
        newHandler = qobject_cast<AbstractRequestHandler *>(pl.instance());
        if(0 != newHandler) {
            qDebug() << "instance created";
            qDebug() << "name " << newHandler->name();
        } else {
            qDebug() << "cannot creeate an instance";
        }
    } else {
        qDebug() << "FAILED to load plugin from " << filepath << ". Reason: " << pl.errorString();
    }

    if(newHandler != 0) {
        qDebug() << "Plugin " << newHandler->name() << " added to the handlers; Settings stored under key " << settingsKey;
        handlers.push_back(HandlerData(newHandler, settingsKey));
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
            qDebug() << "HANDLER MANAGER comparing " << contextRoot << " and " << handlers[i].getContextRoot();
            if(contextRoot == handlers[i].getContextRoot()) {
                list.removeAt(0);
                QString relativePath = "/" + list.join("/");
//                request->setRelativePath(relativePath);
                return handlers[i];
            }
        }
    }

    return defaultHandler;
}

