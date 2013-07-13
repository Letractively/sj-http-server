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


#include "fileappender.h"
#include "fileappenderinternalholder.h"
#include <QString>
#include <QStringList>

namespace SJ {

FileAppender::FileAppender()
    :f(0), rotatedFileTimestampPattern("yyyyMMddhhmmsszzz"), rotateByMaxSize(0)
{
}


QStringList FileAppender::supportedParams()
{
    QStringList list;
    list.append("filename");
    list.append("rotated-file-timestamp-pattern");
    list.append("rotate-at-file-size-of");
    return list;
}

void FileAppender::appendLine(const QString & line)
{
    if(f == 0) {
        f = FileAppenderInternalHolder::getInstance().getFAI(filename);
        f->setMaxSize(rotateByMaxSize);
        f->setTimestampPattern(rotatedFileTimestampPattern);
    }
    f->appendLine(line);
}

bool FileAppender::setProperty(const QString &name, const QString &value) {
    if(name == "filename") {
        filename = value;
        return true;
    } else if(name == "rotated-file-timestamp-pattern") {
        rotatedFileTimestampPattern = value;
        return true;
    } else if(name == "rotate-at-file-size-of") {
        bool ok;
        int val = QVariant(value).toInt(&ok);
        if(ok) {
            rotateByMaxSize = val;
        }
    }

    return false;
}

} // namespace SJ
