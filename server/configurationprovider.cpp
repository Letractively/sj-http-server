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

#include "configurationprovider.h"

namespace SJ {

ConfigurationProvider * ConfigurationProvider::instance = 0;
Logger & ConfigurationProvider::logger = LoggerFactory::instance().getLogger();

ConfigurationProvider * ConfigurationProvider::getInstance()
{
    return instance;
}


ConfigurationProvider::ConfigurationProvider()
    : listenPort(-1)
{
    if(instance != 0) {
        LOG_WARN(logger, "Configuration has already been loaded, server reconfiguration is not supported");
        return;
    }
    instance = this;
}

ConfigurationProvider::~ConfigurationProvider()
{
    delete instance;
}


QHostAddress ConfigurationProvider::getListenInterface() const
{
    return listenInterface;
}

int ConfigurationProvider::getListenPort() const
{
    return listenPort;
}

QString ConfigurationProvider::getWwwPath() const
{
    return wwwPath;
}

QList<HandlerConfiguration> ConfigurationProvider::getHandlers() const
{
    return handlers;
}

bool ConfigurationProvider::loaded() const {
    return false;
}

}

