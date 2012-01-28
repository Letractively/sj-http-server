#ifndef REQUESTPROCESSINGRUNNABLE_H
#define REQUESTPROCESSINGRUNNABLE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QByteArray>
#include "processingcontext.h"
#include "httpresponse.h"

class RequestProcessingRunnable : public QRunnable
{
public:
    RequestProcessingRunnable(QByteArray * data, ProcessingContext * c, QTcpSocket * socket, QObject * dispatcher);
    virtual ~RequestProcessingRunnable();
    virtual void run();

private:
    QByteArray * data;
    ProcessingContext * context;
    QTcpSocket * socket;
    QObject * dispatcher;
};

#endif // REQUESTPROCESSINGRUNNABLE_H
