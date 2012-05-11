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


#ifndef LOGBUILDER_H
#define LOGBUILDER_H

#include <QString>
#include <QVariant>
#include <QStringList>

namespace SJ {

class LogBuilder
{
public:
    LogBuilder(const QString & msg = "");

    LogBuilder & append(const QString & s);
    LogBuilder & append(const char * s);

    template <typename T> LogBuilder & append(T t)
    {
        QVariant v = t;
        list.append(v.toString());
        return *this;
    }


    QString toString() const;
    operator QString() const;

    void clear();

private:
    QStringList list;
};

} // namespace SJ

#endif // LOGBUILDER_H
