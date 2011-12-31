/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011  Samir Jorina

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "logger.h"
#include "maindialog.h"
#include <QDateTime>

Logger * Logger::logger;

void Logger::init(QListWidget *loggerWidget)
{
    if(0 == logger) {
        logger = new Logger(loggerWidget);
    } else {
        //error
    }
}

Logger & Logger::instance()
{
    if(0 == logger) {
        //error
    }
    return *logger;
}

Logger::Logger(QListWidget * loggerWidget)
    : loggerWidget(loggerWidget)
{
}

void Logger::log(const QString &str)
{
    if(loggerWidget->count() > LOGGER_BUFFER_SIZE) {
        delete loggerWidget->takeItem(0);
    }
    QDateTime currentTime = QDateTime::currentDateTime();
    QString logMessage = currentTime.toString("yyyy-MM-dd HH:mm:ss.zzz ") + str;
    loggerWidget->addItem(logMessage);
    loggerWidget->setCurrentRow(loggerWidget->count() - 1);
}

void Logger::debug(const QString &str)
{
    //if enabled
    log(str);
}


