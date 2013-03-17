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


#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QMutex>
#include "logger.h"

namespace SJ {

/**
  @brief Factory class creating Logger objects

  Supports configuration via XML files like:

<?xml version="1.0" encoding="UTF-8" ?>
<sj:loggers xmlns:sj="http://sj-http-server.googlecode.com/logger">
    <sj:logger name="mylogger" level="DEBUG">
        <sj:appenders>
            <sj:appender type="console"/>
            <sj:appender type="file">
                <sj:appenderParam name="filename">mylog.log</sj:appenderParam>
            </sj:appender>
        </sj:appenders>
    </sj:logger>
    <sj:logger name="mylogger2" level="INFO">
        <sj:appenders>
            <sj:appender type="console"/>
        </sj:appenders>
    </sj:logger>
</sj:loggers>

  */
class LoggerFactory
{

public:

    /**
      @brief Destructor
      */
    ~LoggerFactory();

    /**
      @brief returns singleton of the factory
      @return singleton
      */
    static LoggerFactory & instance();

    /**
      @brief loads configuration from a given configuration file

      Call to this function is optional. A defualt configuration file sjlog.xml will be loaded at
        first call to getLogger. Configuration can be loaded once only.

        @param confFile name (and path) to configuration file
      */
    void loadConfig(const QString & confFile = "sjlog.xml");


    /**
      @brief reference to a logger with given name

      If given logger does not exist, it will be created with the default configuration
        (INFO log level and ConsoleAppender)

      @param loggerName name of the logger
      @return logger with given name
      */
    Logger & getLogger(const QString & loggerName = "sj-default-logger");

    /**
      @brief returns list of all loggers configured / created by the factory
      @return list of loggers' names
      */
    QStringList configuredLoggers();

private:
    //LoggerFactory is a singleton, make the constructor private
    LoggerFactory();
    void doLoadConfig(const QString & confFile);

    QMap<QString, Logger *> loggers;
    bool configLoaded;
    QMutex mutex;
};

} // namespace SJ

#endif // LOGGERFACTORY_H
