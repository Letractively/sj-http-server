#ifndef PROCESSINGCONTEXT_H
#define PROCESSINGCONTEXT_H

#include <QByteArray>


class ProcessingContext
{
public:
    ProcessingContext();
private:
    QByteArray * dataArray;
    quint64 bytesRead;
};

#endif // PROCESSINGCONTEXT_H
