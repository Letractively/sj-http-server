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


#ifndef LOGGINGLEVEL_H
#define LOGGINGLEVEL_H

#include <QString>

namespace SJ {


/**
  @brief Level of logging used by Logger to control which messages are going to be printed and which not
  */
class LoggingLevel
{
public:

    /**
      @brief logging levels

      ALL - all messages are printed (equivalent to TRACE)
      TRACE - all messages will be printed
      DEBUG - all messages except TRACE will be printed
      INFO - all messages except TRACE and DEBUG will be printed
      WARN - only WARN and ERROR messages will be pritned
      ERROR - only ERROR messages will be printd
      NONE - no messages will be printed
      */
    enum Level {ALL, TRACE, DEBUG, INFO, WARN, ERROR, NONE};


    /**
      @brief returns string representation of a log level

      For ALL and NONE empty string is returned

      @param level level to be transformed into string
      @return string representation
      */
    static QString levelToString(Level level);

    /**
      @brief transforms string representation of a log level into Level

      Case insensitive. Levels are not supported by this method. If unable to recognize string, NONE is returned

      @param level string to be transformed into Level
      @return Level represented by string
      */
    static Level stringToLevel(const QString & level);

};

} // namespace SJ

#endif // LOGGINGLEVEL_H
