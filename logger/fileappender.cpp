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


#include "fileappender.h"
#include "fileappenderinternalholder.h"
#include <QString>
#include <QStringList>

namespace SJ {

FileAppender::FileAppender()
{
}


QStringList FileAppender::supportedParams()
{
    QStringList list;
    list.append("filename");
    return list;
}

void FileAppender::appendLine(const QString & line)
{
    if(f != 0) {
        f->appendLine(line);
    }
}

bool FileAppender::setProperty(const QString &name, const QString &value) {
    if(name == "filename") {
        f = FileAppenderInternalHolder::getInstance().getFAI(value);
        return true;
    }

    return false;
}

} // namespace SJ
