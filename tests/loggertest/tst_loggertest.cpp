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


#include <QtCore/QString>
#include <QtTest/QtTest>

#include "logger.h"
#include "loggerfactory.h"
#include "testcommon.h"
#include "consoleappender.h"
#include "logbuilder.h"

using namespace SJ;

class LoggerTest : public QObject
{
    Q_OBJECT
    
public:
    LoggerTest();

private Q_SLOTS:
    void testCodeLogger();
    void testLoggerFactory();
    void testLoggerConfig();
};

LoggerTest::LoggerTest()
{
    LoggerFactory::instance().loadConfig("tests/loggertest/sjlog.xml");
}

void LoggerTest::testCodeLogger()
{
    Logger logger;
    logger.addAppender(new ConsoleAppender, true);
    ASSERT(! logger.isTraceEnabled());
    ASSERT(! logger.isDebugEnabled());
    ASSERT(! logger.isInfoEnabled());
    ASSERT(! logger.isWarnEnabled());
    ASSERT(! logger.isErrorEnabled());

    logger.setLevel(LoggingLevel::Level::ALL);
    ASSERT(logger.isTraceEnabled());
    ASSERT(logger.isDebugEnabled());
    ASSERT(logger.isInfoEnabled());
    ASSERT(logger.isWarnEnabled());
    ASSERT(logger.isErrorEnabled());


    logger.setLevel(LoggingLevel::Level::INFO);
    ASSERT(! logger.isTraceEnabled());
    ASSERT(! logger.isDebugEnabled());
    ASSERT(logger.isInfoEnabled());
    ASSERT(logger.isWarnEnabled());
    ASSERT(logger.isErrorEnabled());
}

void LoggerTest::testLoggerFactory()
{
    Logger & logger = LoggerFactory::instance().getLogger("unconfigured-logger");
    ASSERT(logger.isDebugEnabled() == false);
}

void LoggerTest::testLoggerConfig()
{
    Logger & configuredLogger = LoggerFactory::instance().getLogger("mylogger");
    ASSERT(configuredLogger.isDebugEnabled());
}



QTEST_APPLESS_MAIN(LoggerTest)

#include "tst_loggertest.moc"
