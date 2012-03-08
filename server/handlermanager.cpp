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

#include <QPluginLoader>


const QString HandlerManager::PLUGIN_GROUP_NAME="plugins";
const QString HandlerManager::PLUGIN_FILE_PATH = "file.path";
const QString HandlerManager::PLUGIN_CONTEXT_ROOT = "context.root";
const QString HandlerManager::PLUGIN_SETTINGS_KEY = "settings.key";



HandlerManager::HandlerManager()
{
    defaultHandler = HandlerData("", new RequestHandler, "DefaultRequestHandler");
    loadPluginsFromConfig();
}


QString HandlerManager::registerHandler(const QString & filePath, const QString & contextRoot, const QString & settingsKey)
{
    AbstractRequestHandler * newHandler = loadPlugin(filePath, contextRoot, settingsKey);

    if(0 != newHandler) {
        persistHandlerConfig(filePath, contextRoot);

        return newHandler->name();
    }

    return "";
}


void HandlerManager::loadPluginsFromConfig()
{
    QSettings & settings = Utils::getSettings();

    int size = settings.beginReadArray(PLUGIN_GROUP_NAME);

    for(int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        loadPlugin(settings.value(PLUGIN_FILE_PATH).toString(), settings.value(PLUGIN_CONTEXT_ROOT).toString(), settings.value(PLUGIN_SETTINGS_KEY).toString());
    }

    settings.endArray();
}

void HandlerManager::persistHandlerConfig(const QString & filepath, const QString & contextRoot)
{
    QSettings & settings = Utils::getSettings();

    int size = settings.beginReadArray(PLUGIN_GROUP_NAME);
    settings.endArray();

    settings.beginWriteArray(PLUGIN_GROUP_NAME);
    settings.setArrayIndex(size);
    settings.setValue(PLUGIN_FILE_PATH, filepath);
    settings.setValue(PLUGIN_CONTEXT_ROOT, contextRoot);
    settings.endArray();
    settings.sync();
}

AbstractRequestHandler * HandlerManager::loadPlugin(const QString & filepath, const QString & contextRoot, const QString & settingsKey)
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

        //check if plugin is already loaded
        bool alreadySet = false;

        for(int i = 0; i < handlers.size(); ++i) {
            if(newHandler->name() == handlers[i].getHandler()->name()
                    && contextRoot == handlers[i].getContextRoot() ) {
                alreadySet = true;
                break;
            }
        }

        if(!alreadySet) {
            qDebug() << "Plugin " << newHandler->name() << " added to the handlers; Context root is " << contextRoot;
            handlers.push_back(HandlerData(contextRoot, newHandler, settingsKey));
        } else {
            qDebug() << "Plugin already set: "<< newHandler->name() << "for context root " << contextRoot;
        }
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
                request->setRelativePath(relativePath);
                return handlers[i];
            }
        }
    }

    return defaultHandler;
}

