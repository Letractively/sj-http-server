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


#include "logger.h"
#include "logbuilder.h"
#include <QDateTime>

namespace SJ {

Logger::Logger()
    : logLevel(LoggingLevel::NONE)
{
}

Logger::~Logger()
{
    for(int i = 0; i < appendersToDelete.size(); ++i) {
        delete appendersToDelete.at(i);
    }
}

void Logger::trace(const QString & msg, const char * filename, int lineNumber) const
{
    doLog(LoggingLevel::TRACE, msg, filename, lineNumber);
}

void Logger::debug(const QString & msg, const char * filename, int lineNumber) const
{
    doLog(LoggingLevel::DEBUG, msg, filename, lineNumber);
}

void Logger::info(const QString & msg, const char * filename, int lineNumber) const
{
    doLog(LoggingLevel::INFO, msg, filename, lineNumber);
}

void Logger::warn(const QString & msg, const char * filename, int lineNumber) const
{
    doLog(LoggingLevel::WARN, msg, filename, lineNumber);
}

void Logger::error(const QString & msg, const char * filename, int lineNumber) const
{
    doLog(LoggingLevel::ERROR, msg, filename, lineNumber);
}


bool Logger::isTraceEnabled() const
{
    return isLevelEnabled(LoggingLevel::TRACE);
}

bool Logger::isDebugEnabled() const
{
    return isLevelEnabled(LoggingLevel::DEBUG);
}

bool Logger::isInfoEnabled() const
{
    return isLevelEnabled(LoggingLevel::INFO);
}

bool Logger::isWarnEnabled() const
{
    return isLevelEnabled(LoggingLevel::WARN);
}

bool Logger::isErrorEnabled() const
{
    return isLevelEnabled(LoggingLevel::ERROR);
}



void Logger::setLevel(const LoggingLevel::Level & level)
{
    logLevel = level;
}

void Logger::addAppender(AbstractAppender * appender, bool shouldDelete)
{
    appenders.append(appender);
    if(shouldDelete) {
        appendersToDelete.append(appender);
    }
}

void Logger::doLog(const LoggingLevel::Level &level, const QString & msg, const char * filename, int lineNumber) const
{
    if(isLevelEnabled(level)) {
        LogBuilder lb;
        lb.append(timestamp()).append(" ").append(LoggingLevel::levelToString(level));

        if(filename != 0 && strlen(filename) > 0) {
            lb.append(" [").append(filename);
            if(lineNumber > 0) {
                lb.append(":").append(lineNumber);
            }
            lb.append("]");
        }


        lb.append(" ").append(msg);
        for(int i = 0; i < appenders.size(); ++i) {
            appenders.at(i)->appendLine(lb);
        }
    }
}

bool Logger::isLevelEnabled(const LoggingLevel::Level & level) const
{
    return logLevel <= level;
}

QString Logger::timestamp()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
}

} //namespace SJ
