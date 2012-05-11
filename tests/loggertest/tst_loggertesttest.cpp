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


#include <QtCore/QString>
#include <QtTest/QtTest>

#include "logger.h"
#include "testcommon.h"
#include "consoleappender.h"

using namespace SJ;
using namespace SJSERVER;

class LoggertestTest : public QObject
{
    Q_OBJECT
    
public:
    LoggertestTest();
    
private Q_SLOTS:
    void testCase1();
};

LoggertestTest::LoggertestTest()
{
}

void LoggertestTest::testCase1()
{
    Logger logger;
    logger.addAppender(new ConsoleAppender, true);
    QVERIFY(! logger.isTraceEnabled());
    QVERIFY(! logger.isDebugEnabled());
    QVERIFY(! logger.isInfoEnabled());
    QVERIFY(! logger.isWarnEnabled());
    QVERIFY(! logger.isErrorEnabled());

    logger.setLevel(LoggingLevel::ALL);
    QVERIFY(logger.isTraceEnabled());
    QVERIFY(logger.isDebugEnabled());
    QVERIFY(logger.isInfoEnabled());
    QVERIFY(logger.isWarnEnabled());
    QVERIFY(logger.isErrorEnabled());


    logger.setLevel(LoggingLevel::INFO);
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

QTEST_APPLESS_MAIN(LoggertestTest)

#include "tst_loggertesttest.moc"
