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

#include "xmlconfigurationprovider.h"

namespace SJ {

XmlConfigurationProvider::XmlConfigurationProvider()
{
    doParse("sj-http-server.xml");
}

XmlConfigurationProvider::XmlConfigurationProvider(const QString & configFile)
{
    doParse(configFile);
}

void XmlConfigurationProvider::doParse(const QString &configFile)
{
    //read settings from a file
    QFile file(configFile);
    if(!file.exists()) {
        LOG_WARN(logger, LogBuilder("File ").append(configFile).append(" not found, server is not configured"));
        return;
    }

    QXmlInputSource source(&file);
    XmlConfigurationParser handler(this);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);
    bool parseResult = reader.parse(source);
    if(!parseResult) {
        listenInterface = "";
        listenPort = 0;
        LOG_WARN(logger, LogBuilder("Unable to parse config from file").append(configFile).append(". Error: ").append(handler.errorString()));
    }
}

XmlConfigurationParser::XmlConfigurationParser(XmlConfigurationProvider * provider)
    : provider(provider)
{

}

}
