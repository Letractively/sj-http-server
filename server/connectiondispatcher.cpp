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


#include "connectiondispatcher.h"
#include <QTcpSocket>
#include "processingcontext.h"

ConnectionDispatcher::ConnectionDispatcher(QObject *parent) :
    QThread(parent), threadPool(0), processingContexts(0)
{
    threadPool = new QThreadPool();
    processingContexts = new QMap<int, ProcessingContext *>();
}

ConnectionDispatcher::~ConnectionDispatcher()
{
    if(0 != threadPool) {
        delete threadPool;
    }

    threadPool = 0;

    if(0 != processingContexts) {
        QMapIterator<int, ProcessingContext *> i(*processingContexts);
        while (i.hasNext()) {
            i.next();
            if(0 != i.value()) {
                delete i.value();
            }
        }
        delete processingContexts;
    }

    processingContexts = 0;
}

void ConnectionDispatcher::dataReadySlot()
{
    QTcpSocket * socket = (QTcpSocket *) sender();

    ProcessingContext * context;
    if(processingContexts->contains(socket->socketDescriptor())) {
        context = processingContexts->operator [](socket->socketDescriptor());
    } else {
        context = new ProcessingContext();
    }

    QByteArray * data = new QByteArray;
    *data = socket->readAll();
    RequestProcessingRunnable * runnable = new RequestProcessingRunnable(data, context, socket, this);
    threadPool->start(runnable);

}

void ConnectionDispatcher::disconnectedSlot()
{
    QTcpSocket * socket = (QTcpSocket *) sender();
    if(processingContexts->contains(socket->socketDescriptor())) {
        processingContexts->remove(socket->socketDescriptor());
    }

    socket->deleteLater();
}

void ConnectionDispatcher::dispatchConnection(const int socketDescriptor)
{
    QTcpSocket * socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReadySlot()));
}

void ConnectionDispatcher::responseReadySlot(HttpResponse * response, QTcpSocket * socket)
{
    response->writeToSocket(socket);
    delete response;
}

void ConnectionDispatcher::socketErrorSlot(QTcpSocket::SocketError socketError)
{
    emit errorSignal(socketError);
}

void ConnectionDispatcher::run()
{
    exec();
}
