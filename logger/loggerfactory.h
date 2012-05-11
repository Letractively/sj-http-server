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


#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

#include <QString>
#include <QMap>
#include <QMutex>
#include "logger.h"

namespace SJ {

class LoggerFactory
{

public:
    ~LoggerFactory();
    static LoggerFactory & instance();
    void loadConfig(const QString & confFile = "sjlog.xml");
    Logger & getLogger(const QString & loggerName = "sj-default-logger");

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
