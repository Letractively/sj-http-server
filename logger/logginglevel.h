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


#ifndef LOGGINGLEVEL_H
#define LOGGINGLEVEL_H

#include <QString>

namespace SJ {

class LoggingLevel
{
public:
    LoggingLevel();

    enum Level {ALL, TRACE, DEBUG, INFO, WARN, ERROR, NONE};

    static QString levelToString(Level level);
    static Level stringToLevel(const QString & level);

};

} // namespace SJ

#endif // LOGGINGLEVEL_H
