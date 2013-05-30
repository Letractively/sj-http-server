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

private:
    const Logger & scLogger;
    
private Q_SLOTS:
    void testCase1();
    void testCase2();
    void testCase3();
    void testCase4();
};

LoggerTest::LoggerTest()
    :scLogger(LoggerFactory::instance().getLogger("scLogger"))
{
}

void LoggerTest::testCase1()
{
    Logger logger;
    logger.addAppender(new ConsoleAppender, true);
    QVERIFY(! logger.isTraceEnabled());
    QVERIFY(! logger.isDebugEnabled());
    QVERIFY(! logger.isInfoEnabled());
    QVERIFY(! logger.isWarnEnabled());
    QVERIFY(! logger.isErrorEnabled());

    logger.setLevel(LoggingLevel::Level::ALL);
    QVERIFY(logger.isTraceEnabled());
    QVERIFY(logger.isDebugEnabled());
    QVERIFY(logger.isInfoEnabled());
    QVERIFY(logger.isWarnEnabled());
    QVERIFY(logger.isErrorEnabled());


    logger.setLevel(LoggingLevel::Level::INFO);
    QVERIFY(! logger.isTraceEnabled());
    QVERIFY(! logger.isDebugEnabled());
    QVERIFY(logger.isInfoEnabled());
    QVERIFY(logger.isWarnEnabled());
    QVERIFY(logger.isErrorEnabled());

    LOG_INFO(logger,"test message");
    logger.info("test message two");
    LOG_DEBUG(logger, "this should not show up");
    logger.debug("this should not show up");

}

void LoggerTest::testCase2()
{
    Logger & logger = LoggerFactory::instance().getLogger();
    logger.info("logger factory can produce loggers :)");
    logger.debug("by default info level is enabled");
    ASSERT(logger.isDebugEnabled() == false);

    logger.info(LogBuilder(LoggerFactory::instance().configuredLoggers(), " "));
}

void LoggerTest::testCase3()
{
    SJ::LogBuilder lb("Hello to LogBuilder.");
    lb.append(" This is a string, then goes an int ").append(12);
    lb.append(" and finally a double ").append(3.14);
    qDebug() << lb.toString();

    scLogger.info(lb);
}

void LoggerTest::testCase4()
{
    const Logger & logger = LoggerFactory::instance().getLogger("mylogger");
    logger.debug("test123");
    LOG_DEBUG(logger, "test321");
}

QTEST_APPLESS_MAIN(LoggerTest)

#include "tst_loggertest.moc"
