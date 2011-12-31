#ifndef IMAGESERVER_H
#define IMAGESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

class ImageServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ImageServer(QObject *parent = 0);
    ~ImageServer();
    static QHostAddress createAddress(QString interface);

private slots:
    void threadDestroyedSlot();
    void threadFinishedSlot();

protected:
    void incomingConnection(int socketDescriptor);

};

#endif // IMAGESERVER_H
