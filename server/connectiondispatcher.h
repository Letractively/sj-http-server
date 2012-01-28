/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Samir Jorina

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


#ifndef CONNECTIONDISPATCHER_H
#define CONNECTIONDISPATCHER_H

#include <QThread>
#include <QThreadPool>
#include <QTcpSocket>
#include <QMap>

#include "requestprocessingrunnable.h"
#include "processingcontext.h"

class ConnectionDispatcher : public QThread
{
    Q_OBJECT
public:
    explicit ConnectionDispatcher(QObject *parent = 0);
    ~ConnectionDispatcher();
    void dispatchConnection(const int socketDescriptor);
    void run();


private:
    QThreadPool * threadPool;
    QMap<int, ProcessingContext *> * processingContexts;

signals:
    void errorSignal(QTcpSocket::SocketError socketErrorSlot);

private slots:
    void dataReadySlot();
    void disconnectedSlot();
    void socketErrorSlot(QTcpSocket::SocketError socketErrorSlot);
    void responseReadySlot(HttpResponse * response, QTcpSocket * socket);



};

#endif // CONNECTIONDISPATCHER_H
