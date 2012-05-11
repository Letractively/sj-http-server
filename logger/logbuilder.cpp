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


#include "logbuilder.h"

namespace SJ {

LogBuilder::LogBuilder(const QString &msg)
{
    if(msg != "") {
        list.append(msg);
    }
}

LogBuilder::LogBuilder(const QStringList & stringList)
{
    append(stringList);
}

LogBuilder & LogBuilder::append(const QString & s)
{
    list.append(s);
    return *this;
}

LogBuilder & LogBuilder::append(const QStringList & stringList)
{
    list.append(stringList);
    return *this;
}


LogBuilder & LogBuilder::append(const char * s)
{
    list.append(QString(s));
    return *this;
}

void LogBuilder::clear() {
    list.clear();
}

QString LogBuilder::toString() const
{
    QString str = "";
    for(int i = 0; i < list.size(); ++i) {
        str += list.at(i);
    }

    return str;
}

LogBuilder::operator QString() const
{
    return toString();
}

} //namespace SJ
