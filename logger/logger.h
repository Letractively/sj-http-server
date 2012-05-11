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

namespace SJ {

class Logger {
public:
    Logger();
    ~Logger();

    void trace(const QString & msg, const char * filename = 0, int lineNumber = 0);
    void debug(const QString & msg, const char * filename = 0, int lineNumber = 0);
    void info(const QString & msg, const char * filename = 0, int lineNumber = 0);
    void warn(const QString & msg, const char * filename = 0, int lineNumber = 0);
    void error(const QString & msg, const char * filename = 0, int lineNumber = 0);

    bool isTraceEnabled() const;
    bool isDebugEnabled() const;
    bool isInfoEnabled() const;
    bool isWarnEnabled() const;
    bool isErrorEnabled() const;

    void setLevel(const LoggingLevel::Level & level);
    void addAppender(AbstractAppender * appender, bool shouldDelete = false);

private: //methods
    void doLog(const LoggingLevel::Level & level, const QString &msg, const char *filename, int lineNumber);
    bool isLevelEnabled(const LoggingLevel::Level &level) const;
    QString timestamp();

private: //fields
    LoggingLevel::Level logLevel;
    QVector<AbstractAppender *> appenders;
    QVector<AbstractAppender *> appendersToDelete;
};

} //namespace SJ
#endif // LOGGER_H
