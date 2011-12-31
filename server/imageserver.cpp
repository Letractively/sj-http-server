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

