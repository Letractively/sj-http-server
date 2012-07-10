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


#ifndef LOGGER_H
#define LOGGER_H

#include "logginglevel.h"
#include "abstractappender.h"

#include <QVector>

namespace SJ {

#if defined(__FILE__) && defined(__LINE__)
#define LOG_TRACE(logger,msg) logger.trace(msg, __FILE__, __LINE__)
#define LOG_DEBUG(logger,msg) logger.debug(msg, __FILE__, __LINE__)
#define LOG_INFO(logger,msg) logger.info(msg, __FILE__, __LINE__)
#define LOG_WARN(logger,msg) logger.warn(msg, __FILE__, __LINE__)
#define LOG_ERROR(logger,msg) logger.error(msg, __FILE__, __LINE__)
#elif defined(__FILE__)
#define LOG_TRACE(logger,msg) logger.trace(msg, __FILE__, 0)
#define LOG_DEBUG(logger,msg) logger.debug(msg, __FILE__, 0)
#define LOG_INFO(logger,msg) logger.info(msg, __FILE__, 0)
#define LOG_WARN(logger,msg) logger.warn(msg, __FILE__, 0)
#define LOG_ERROR(logger,msg) logger.error(msg, __FILE__, 0)
#else
#define LOG_TRACE(logger,msg) logger.trace(msg, 0, 0)
#define LOG_DEBUG(logger,msg) logger.debug(msg, 0, 0)
#define LOG_INFO(logger,msg) logger.info(msg, 0, 0)
#define LOG_WARN(logger,msg) logger.warn(msg, 0, 0)
#define LOG_ERROR(logger,msg) logger.error(msg, 0, 0)
#endif


/**
  @brief Logger class is used to log different events in an application.

  It is recommended that Loggers are created by means of LoggerFactory

  Header file defines the following macros:
    LOG_TRACE(logger,msg)
    LOG_DEBUG(logger,msg)
    LOG_INFO(logger,msg)
    LOG_WARN(logger,msg)
    LOG_ERROR(logger,msg)
  which automatically insert source file name and line number (if available) into the log message
  */
class Logger {
public:


    /**
      @brief constructs logger object with logging level set to NONE (logging is turned off)
      */
    Logger();

    /**
      @brief Destructs logger and deletes appenders (if required, see addAppender)
      */
    ~Logger();

    /**
      @brief logs message at TRACE logging level

      See also LOG_TRACE

      @param msg message to print
      @param filename name of a source code file (by default - do not print)
      @param lineNumber numer of a source code line in which message was printed (by default - do not priint)
      */
    void trace(const QString & msg, const char * filename = 0, int lineNumber = 0) const;


    /**
      @brief logs message at DEBUG logging level

      See also LOG_DEBUG

      @param msg message to print
      @param filename name of a source code file (by default - do not print)
      @param lineNumber numer of a source code line in which message was printed (by default - do not priint)
      */
    void debug(const QString & msg, const char * filename = 0, int lineNumber = 0) const;


    /**
      @brief logs message at INFO logging level

      See also LOG_INFO

      @param msg message to print
      @param filename name of a source code file (by default - do not print)
      @param lineNumber numer of a source code line in which message was printed (by default - do not priint)
      */
    void info(const QString & msg, const char * filename = 0, int lineNumber = 0) const;


    /**
      @brief logs message at WARN logging level

      See also LOG_WARN

      @param msg message to print
      @param filename name of a source code file (by default - do not print)
      @param lineNumber numer of a source code line in which message was printed (by default - do not priint)
      */
    void warn(const QString & msg, const char * filename = 0, int lineNumber = 0) const;


    /**
      @brief logs message at ERROR logging level

      See also LOG_ERROR

      @param msg message to print
      @param filename name of a source code file (by default - do not print)
      @param lineNumber numer of a source code line in which message was printed (by default - do not priint)
      */
    void error(const QString & msg, const char * filename = 0, int lineNumber = 0) const;


    /**
      @brief tests if TRACE log level is enabled
      @return true if TRACE messages will be printed, false otherwise
      */
    bool isTraceEnabled() const;

    /**
      @brief tests if DEBUG log level is enabled
      @return true if DEBUG messages will be printed, false otherwise
      */
    bool isDebugEnabled() const;

    /**
      @brief tests if INFO log level is enabled
      @return true if INFO messages will be printed, false otherwise
      */
    bool isInfoEnabled() const;

    /**
      @brief tests if WARN log level is enabled
      @return true if WARN messages will be printed, false otherwise
      */
    bool isWarnEnabled() const;

    /**
      @brief tests if ERROR log level is enabled
      @return true if ERROR messages will be printed, false otherwise
      */
    bool isErrorEnabled() const;


    /**
      @brief sets logging level of a specified logger to a given level
      @param level logging level to set
     */
    void setLevel(const LoggingLevel::Level & level);

    /**
      @brief adds appender to a logger

      Logs logged by this logger will be directed to all added appenders

      @param appender appender to add
      @param shouldDelete if set to true, appender will be deleted when Logger is destroyed
      */
    void addAppender(AbstractAppender * appender, bool shouldDelete = false);

private: //methods
    void doLog(const LoggingLevel::Level & level, const QString &msg, const char *filename, int lineNumber) const;
    bool isLevelEnabled(const LoggingLevel::Level &level) const;
    static QString timestamp();

private: //fields
    LoggingLevel::Level logLevel;
    mutable QVector<AbstractAppender *> appenders;
    QVector<AbstractAppender *> appendersToDelete;
};

} //namespace SJ
#endif // LOGGER_H
