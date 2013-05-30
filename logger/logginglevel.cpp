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


#include "logginglevel.h"

namespace SJ {

QString LoggingLevel::levelToString(Level level)
{
    switch(level) {
    case Level::TRACE: return "TRACE";
    case Level::DEBUG: return "DEBUG";
    case Level::INFO: return "INFO";
    case Level::WARN: return "WARN";
    case Level::ERROR: return "ERROR";
    default: break;
    }
    return "";
}

LoggingLevel::Level LoggingLevel::stringToLevel(const QString & level)
{
    if(level.toUpper() == "TRACE") return Level::TRACE;
    if(level.toUpper() == "DEBUG") return Level::DEBUG;
    if(level.toUpper() == "INFO") return Level::INFO;
    if(level.toUpper() == "WARN") return Level::WARN;
    if(level.toUpper() == "ERROR") return Level::ERROR;

    return Level::NONE;

}

} // namespace SJ
