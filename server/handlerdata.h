#ifndef HANDLERDATA_H
#define HANDLERDATA_H

#include <QString>
#include "abstractrequesthandler.h"

class HandlerData
{
public:
    HandlerData();
    HandlerData(const QString & contextPath, AbstractRequestHandler * handler);
    ~HandlerData();
    QString getContextPath() { return contextPath; }
    AbstractRequestHandler * getHandler() {return handler;}
private:
    QString contextPath;
    AbstractRequestHandler * handler;
};

#endif // HANDLERDATA_H
