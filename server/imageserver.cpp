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


#include "imageserver.h"
#include "logger.h"
#include "requestprocessingthread.h"

#include <QFile>
#include <QDebug>

#include "httprequest.h"

ImageServer::ImageServer(QObject *parent) :
    QTcpServer(parent)
{
}

ImageServer::~ImageServer()
{
    close();
}

QHostAddress ImageServer::createAddress(QString interface)
{
    if(interface == "localhost" || interface == "127.0.0.1") {
        return QHostAddress::LocalHost;
    }

    if(interface == "any") {
        return QHostAddress::Any;
    }

    return QHostAddress(interface);
}

void ImageServer::incomingConnection(int socketDescriptor)
{
    RequestProcessingThread * thread = new RequestProcessingThread(socketDescriptor);
    connect(thread, SIGNAL(destroyed()), this, SLOT(threadDestroyedSlot()));
    connect(thread, SIGNAL(finished()), this, SLOT(threadFinishedSlot()));
    thread->start();
    return;
}

void ImageServer::threadDestroyedSlot()
{
    qDebug() << "thread destroyed";
}

void ImageServer::threadFinishedSlot()
{
    qDebug() << "thread finished";
    sender()->deleteLater();
}

