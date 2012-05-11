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


#include "logginglevel.h"

namespace SJ {

LoggingLevel::LoggingLevel()
{
}

QString LoggingLevel::levelToString(Level level)
{
    switch(level) {
    case TRACE: return "TRACE";
    case DEBUG: return "DEBUG";
    case INFO: return "INFO";
    case WARN: return "WARN";
    case ERROR: return "ERROR";
    default: break;
    }
    return "";
}

LoggingLevel::Level LoggingLevel::stringToLevel(const QString & level)
{
    if(level.toUpper() == "TRACE") return TRACE;
    if(level.toUpper() == "DEBUG") return DEBUG;
    if(level.toUpper() == "INFO") return INFO;
    if(level.toUpper() == "WARN") return WARN;
    if(level.toUpper() == "ERROR") return ERROR;

    return NONE;

}

} // namespace SJ
