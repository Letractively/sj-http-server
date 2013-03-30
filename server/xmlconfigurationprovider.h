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

#ifndef XMLCONFIGURATIONPROVIDER_H
#define XMLCONFIGURATIONPROVIDER_H

#include "configurationprovider.h"
#include <QXmlDefaultHandler>

namespace SJ {

class XmlConfigurationParser;

class XmlConfigurationProvider : public ConfigurationProvider
{
public:
    XmlConfigurationProvider();
    XmlConfigurationProvider(const QString & configFile);
private:
    void doParse(const QString & configFile);

    friend class XmlConfigurationParser;
};

class XmlConfigurationParser : public QXmlDefaultHandler
{
public:
    XmlConfigurationParser(XmlConfigurationProvider * provider);

private:
    XmlConfigurationProvider * provider;
};


}

#endif // XMLCONFIGURATIONPROVIDER_H
