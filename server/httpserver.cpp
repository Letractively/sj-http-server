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


#include "httpserver.h"
#include "logger.h"
#include "requestprocessingthread.h"

#include <QFile>

#include "httprequest.h"

namespace SJ {

const Logger & HttpServer::logger = LoggerFactory::instance().getLogger("sj-server-logger");

HttpServer::HttpServer(QObject *parent) :
    QTcpServer(parent)
{

}

HttpServer::~HttpServer()
{
    close();
}

void HttpServer::close()
{
    if(isListening()) {
        if(logger.isInfoEnabled()) {
            LOG_INFO(logger, "Server stopped");
        }

        QTcpServer::close();
        emit serverStoppedSignal();
    }
}

bool HttpServer::listen(const QHostAddress &address, quint16 port)
{
    if(logger.isInfoEnabled()) {
        LOG_INFO(logger, LogBuilder("Server started. Listening on ").append(address.toString())
                 .append(" port ").append(port));
    }
    return QTcpServer::listen(address, port);
}

void HttpServer::incomingConnection(int socketDescriptor)
{
    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, LogBuilder("New connection on socket descriptor ").append(socketDescriptor));
    }
    RequestProcessingThread * thread = new RequestProcessingThread(socketDescriptor);
    connect(thread, SIGNAL(finished()), this, SLOT(threadFinishedSlot()));
    connect(this, SIGNAL(serverStoppedSignal()), thread, SLOT(serverStoppedSlot()));

    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, "RequestProcessingThread execution started");
    }
    thread->start();
}


void HttpServer::threadFinishedSlot()
{
    if(logger.isDebugEnabled()) {
        LOG_DEBUG(logger, "RequestProcessingThread execution finished");
    }
    sender()->deleteLater();
}

} // namespace SJ
