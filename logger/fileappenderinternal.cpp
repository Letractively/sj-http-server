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


#include "fileappenderinternal.h"
#include <QDateTime>

namespace SJ {

FileAppenderInternal::FileAppenderInternal(const QString &filename)
    : file(filename)
{
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    out = new QTextStream(&file);
}

//TODO: use delegating constructor from c++11
FileAppenderInternal::FileAppenderInternal(const FileAppenderInternal & other)
    :file(other.file.fileName())
{
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    out = new QTextStream(&file);
}

FileAppenderInternal::~FileAppenderInternal()
{
    delete out;
    out = 0;
    file.close();
}

void FileAppenderInternal::appendLine(const QString & line)
{
    QMutexLocker locker(&mutex);
    *out << line << "\n";
    out->flush();

    //rotate by size
    if(maxSize > 0 && file.size() > maxSize) {
        delete out;
        file.close();
        file.copy(file.fileName() + "." + produceTimestamp());
        file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        out = new QTextStream(&file);
    }
}

QString FileAppenderInternal::produceTimestamp()
{
    return QDateTime::currentDateTime().toString(timestampPattern);
}

void FileAppenderInternal::setMaxSize(quint64 size)
{
    maxSize = size;
}

void FileAppenderInternal::setTimestampPattern(const QString & pattern)
{
    timestampPattern = pattern;
}

}
