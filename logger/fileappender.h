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


#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H

#include "abstractappender.h"
#include "fileappenderinternal.h"
#include <QString>

namespace SJ {


/**
  @brief Writes log messages to a file

  Not supported yet
  */
class FileAppender : public AbstractAppender
{
public:
    FileAppender();


    /**
      @brief returns type of the appender ("file"). Used when reading logger configuration from file
     */
    static QString type() { return "file"; }

    /**
      @brief returns list of parameters that can be applied to this class of appenders.
      Used when reading logger configuration from file

      Supported parameters are: filename
     */
    static QStringList supportedParams();

    void appendLine(const QString &line);
    virtual bool setProperty(const QString & name, const QString & value);

private:
    FileAppenderInternal * f;
};

} // namespace SJ

#endif // FILEAPPENDER_H
