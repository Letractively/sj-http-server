#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <abstractrequesthandler.h>

class RequestHandler : public AbstractRequestHandler
{
public:
    RequestHandler();
    QString name() { return "default request handler"; }
    HttpResponse handle(HttpRequest *req, QSettings *settings);
};

#endif // REQUESTHANDLER_H
