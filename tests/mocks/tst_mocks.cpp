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


#include <QtCore>
#include <QtTest>
#include <QString>
#include "tcpsocketmock.h"

using namespace SJ;

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
    QByteArray data1;
    data1.append("GET / HTTP/1.1\r\n");
    data1.append("Host: localhost:9090\r\n");
    data1.append("\r\n");

    TcpSocketMock * socket1 = new TcpSocketMock(data1);

    while(socket1->canReadLine()) {
        qDebug() << socket1->readLine();
    }

    socket1->deleteLater();
    qDebug() << "socket1 test OK";

    TcpSocketMock * socket2 = new TcpSocketMock(QByteArray());

    QVERIFY(socket2->bytesAvailable() == 0);
    QVERIFY(socket2->canReadLine() == false);
    socket2->deleteLater();
    qDebug() << "socket2 test OK";

    TcpSocketMock * socket3 = new TcpSocketMock(QByteArray("a"));

    QVERIFY(socket3->bytesAvailable() == 1);
    QVERIFY(socket3->canReadLine()== true);
    QByteArray data3read = socket3->readLine();
    QVERIFY2(data3read.size() == 1, QString::number(data3read.size()).toStdString().c_str());
    QVERIFY(socket3->bytesAvailable() == 0);

    socket3->deleteLater();
    qDebug() << "socket3 test OK";


}


QTEST_APPLESS_MAIN(MockTest)

#include "tst_mocks.moc"
