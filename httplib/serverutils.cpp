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


#include "serverutils.h"
#include "loggerfactory.h"
#include "logbuilder.h"
#include <QStringList>


QString Utils::substring(const QString & str, int beginIndex, int endIndex)
{
    if(endIndex == -1) {
        return str.mid(beginIndex, endIndex);
    } else {
        return str.mid(beginIndex, str.length() - beginIndex - endIndex);
    }
}

QSettings & Utils::getSettings()
{
    static QSettings settings("sj-http-server.ini", QSettings::IniFormat);
    SJ::LoggerFactory::instance().getLogger().trace(SJ::LogBuilder(settings.allKeys()));
    return settings;
}
