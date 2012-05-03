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


#include <QtCore>
#include <QtTest>
#include <QString>
#include "tcpsocketmock.h"

using namespace SJSERVER;

class MockTest : public QObject
{
    Q_OBJECT

public:
    MockTest();

private Q_SLOTS:
    void testTcpSocketMock();
};

MockTest::MockTest()
{

}



void MockTest::testTcpSocketMock()
{
    QByteArray data;
    data.append("GET / HTTP/1.1\n");
    data.append("Host: localhost:9090\n");
    data.append("\n");

    TcpSocketMock * socket = new TcpSocketMock(data);

    while(socket->canReadLine()) {
        qDebug() << socket->readLine();
    }

}


QTEST_APPLESS_MAIN(MockTest)

#include "tst_mocks.moc"
