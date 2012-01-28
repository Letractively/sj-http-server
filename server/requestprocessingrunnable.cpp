#include "requestprocessingrunnable.h"
#include "httpresponse.h"

RequestProcessingRunnable::RequestProcessingRunnable(QByteArray * data, ProcessingContext * c, QTcpSocket * s, QObject * dispatcher)
    : data(data), context(c), socket(s), dispatcher(dispatcher)
{
}

RequestProcessingRunnable::~RequestProcessingRunnable()
{
}


void RequestProcessingRunnable::run()
{
    //process requests...
    QByteArray data2;
    data2.append("All ok !!!");
    HttpResponse * res = new HttpResponse(&data2);

    QMetaObject::invokeMethod(dispatcher, "responseReadySlot", Qt::QueuedConnection, Q_ARG(HttpResponse*, res), Q_ARG(QTcpSocket*, socket));

}
