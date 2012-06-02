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


#ifndef CONSOLEAPPENDER_H
#define CONSOLEAPPENDER_H

#include "abstractappender.h"

#include <QString>
#include <QStringList>
#include <QMutex>

namespace SJ {

/**
  @brief Prints log messages to console

  Multiple objects of this class can be created, and all of them are thread safe
  */
class ConsoleAppender : public AbstractAppender
{
public:

    /**
      @brief returns type of the appender ("console"). Used when reading logger configuration from file
     */
    static QString type() { return "console"; }

    /**
      @brief returns list of parameters that can be applied to this class of appenders.
      Used when reading logger configuration from file

      ConsoleAppender does not support any parameters
     */
    static QStringList supportedParams() { return QStringList(); }

    void appendLine(const QString &line);

private:
    static QMutex mutex;

};
}

#endif // CONSOLEAPPENDER_H
