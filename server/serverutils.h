/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <QString>
#include <QSettings>
#include <QHostAddress>

namespace SJ {

class Utils
{
public:
    static QString substring(const QString & str, int beginIndex, int endIndex = -1);
    static QString version() { return "0.2"; }
    static QSettings & getSettings();
    static QHostAddress createAddress(QString interface);

};

} //namespace SJ

#endif // SERVER_UTILS_H
