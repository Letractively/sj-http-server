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


#ifndef FILEAPPENDERINTERNAL_H
#define FILEAPPENDERINTERNAL_H

#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QFile>
#include <QTextStream>

namespace SJ {

class FileAppenderInternal
{


public:
    FileAppenderInternal(const QString & filename);
    ~FileAppenderInternal();
    void appendLine(const QString & line);
    void setMaxSize(quint64 size);
    void setTimestampPattern(const QString & pattern);

private:
    QFile file;
    QMutex mutex;
    QTextStream * out;
    QString produceTimestamp();
    QString timestampPattern;
    qint64 maxSize;

};

}

#endif // FILEAPPENDERINTERNAL_H
