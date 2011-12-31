#ifndef HANDLERMANAGER_H
#define HANDLERMANAGER_H

#include "abstractrequesthandler.h"
#include "handlerdata.h"
#include "QVector"

class HandlerManager
{
public:
    HandlerManager();
    ~HandlerManager();
    static HandlerManager & instance();
    AbstractRequestHandler * getHandler(HttpRequest * request);

private:
    AbstractRequestHandler * defaultHandler;
    QVector<HandlerData> handlers;
};

#endif // HANDLERMANAGER_H
