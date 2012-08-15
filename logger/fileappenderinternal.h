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


#ifndef FILEAPPENDERINTERNAL_H
#define FILEAPPENDERINTERNAL_H

#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QFile>
#include <QTextStream>

class FileAppenderInternal
{


public:
    FileAppenderInternal(const QString & filename);
    ~FileAppenderInternal();
    void appendLine(const QString & line);

private:
    QFile file;
    QMutex mutex;
    QTextStream * out;

};

#endif // FILEAPPENDERINTERNAL_H
