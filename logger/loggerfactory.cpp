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


#include "loggerfactory.h"
#include "consoleappender.h"
#include "loggerconffileparsehandler.h"

#include <QMutexLocker>
#include <QList>
#include <QFile>
#include <QDebug>
#include <QXmlInputSource>
#include <QXmlSimpleReader>

namespace SJ {

LoggerFactory & LoggerFactory::instance() {
    static LoggerFactory lf;
    return lf;
}

LoggerFactory::LoggerFactory()
    :configLoaded(false)
{
}

LoggerFactory::~LoggerFactory()
{
    QList<QString> keys = loggers.keys();
    for(int i = 0; i < keys.size(); ++i) {
        delete loggers.value(keys.at(i));
    }
}

void LoggerFactory::loadConfig(const QString & confFile)
{
    if(!configLoaded) {
        QMutexLocker locker(&mutex);
        if(!configLoaded) {
            doLoadConfig(confFile);
            configLoaded = true;
        }
    }
}

void LoggerFactory::doLoadConfig(const QString & confFile)
{
    //read logger settings from a file
    QFile file(confFile);
    if(!file.exists()) {
        qWarning() << "File " + confFile + " not found, no loggers configured";
        return;
    }

    QXmlInputSource source(&file);
    LoggerConfFileParseHandler handler(loggers);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);
    bool parseResult = reader.parse(source);
    if(!parseResult) {
        loggers.clear();
        qWarning() << "Unable to parse logger config from file " << confFile << ". Error: " << handler.errorString();
    }


}

Logger & LoggerFactory::getLogger(const QString & loggerName)
{
    if(!configLoaded) {
        loadConfig();
    }
    if(loggers.contains(loggerName)) {
        return *loggers.value(loggerName);
    }

    //create a new logger and apply default settings
    Logger * logger = new Logger;
    logger->addAppender(new ConsoleAppender, true);
    logger->setLevel(LoggingLevel::INFO);
    loggers.insert(loggerName, logger);
    return *logger;
}

QStringList LoggerFactory::configuredLoggers()
{
    return QStringList(loggers.keys());
}

} // namespace SJ
