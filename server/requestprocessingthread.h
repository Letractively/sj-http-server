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

private slots:
    void dataReadySlot();
    void disconnectedSlot();

private:
    QByteArray * dataArray;
    QTcpSocket * socket;
    HttpRequest * request;
    quint64 bytesRead;
    QSettings settings;

    void processRequest();
    void preparePostRequest();

    void parseRequest();
    void parsePart(const QByteArray & partData);
    QString findAttributeValue(const QString & attributeName, const QByteArray & partData);
    QString findHeaderValue(const QString & headerName, const QByteArray & data);
    QByteArray findData(const QByteArray & data);
};

#endif // REQUESTPROCESSINGTHREAD_H
