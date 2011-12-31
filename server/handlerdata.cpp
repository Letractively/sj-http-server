#include "handlerdata.h"

HandlerData::HandlerData()
    :handler(0)
{

}

HandlerData::HandlerData(const QString & contextPath, AbstractRequestHandler * handler)
    : contextPath(contextPath), handler(handler)
{
    if(!contextPath.startsWith("/")) {
        this->contextPath = "/" + contextPath;
    }
}

HandlerData::~HandlerData()
{
}
