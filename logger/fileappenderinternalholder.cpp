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


#include "fileappenderinternalholder.h"

namespace SJ {

FileAppenderInternalHolder & FileAppenderInternalHolder::getInstance()
{
    static FileAppenderInternalHolder holder;
    return holder;
}




FileAppenderInternal * FileAppenderInternalHolder::getFAI(const QString & filename)
{
    QMutexLocker locker(&getFAIMutex);
    if(fMap.contains(filename)) {
        return fMap.value(filename);
    }

    FileAppenderInternal * f = new FileAppenderInternal(filename);
    fMap.insert(filename, f);
    return f;
}



FileAppenderInternalHolder::~FileAppenderInternalHolder()
{
    QMutexLocker locker(&getFAIMutex);

    QList<QString> keys = fMap.keys();
    for(int i = 0; i < keys.size(); ++i) {
        delete fMap.take(keys.at(i));
    }
}

FileAppenderInternalHolder::FileAppenderInternalHolder()
{
}

}
