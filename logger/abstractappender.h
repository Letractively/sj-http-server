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


#ifndef ABSTRACTAPPENDER_H
#define ABSTRACTAPPENDER_H

#include <QString>

namespace SJ {

class AbstractAppender
{
public:
    AbstractAppender() {}
    virtual ~AbstractAppender() {}
    virtual void appendLine(const QString & line) = 0;
    /**
     * @brief Applies a given property to an appender.
     * @return true if appender applied the property successfully, false otherwise
     *   (for example when property name is not recognized or value is incorrect)
     */
    virtual bool setProperty(const QString & /*name*/, const QString & /*value*/) { return false; }
};

}
#endif // ABSTRACTAPPENDER_H
