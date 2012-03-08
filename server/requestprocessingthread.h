/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef REQUESTPROCESSINGTHREAD_H
#define REQUESTPROCESSINGTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QSettings>

#include "httprequest.h"


class RequestProcessingThread : public QThread
{
    Q_OBJECT

public:
    RequestProcessingThread(int socketDescriptor, QObject * parent = 0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void serverStoppedSlot();

private slots:
    void dataReadySlot();
    void disconnectedSlot();

private:
    QByteArray * dataArray;
    QTcpSocket * socket;
    HttpRequest * request;
    quint64 bytesRead;
    QSettings & settings;
    void processRequest();
    void preparePostRequest();

    void parseRequest();
    void parsePart(const QByteArray & partData);
    void parseFormParameters(const QByteArray & partData);
    QString findAttributeValue(const QString & attributeName, const QByteArray & partData);
    QString findHeaderValue(const QString & headerName, const QByteArray & data);
    QByteArray findData(const QByteArray & data);
    QSettings::SettingsMap * readHandlerSettings(const QString & handlerSettingsKey);
};

#endif // REQUESTPROCESSINGTHREAD_H
