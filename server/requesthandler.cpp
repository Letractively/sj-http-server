#include "requesthandler.h"
#include "settingsconstants.h"

RequestHandler::RequestHandler()
{
}

HttpResponse RequestHandler::handle(HttpRequest *req, QSettings *settings)
{
    if(req->getMethod() != HttpRequest::GET) {
        return HttpResponse(HttpResponse::NOT_FOUND);
    }

    QString wwwRoot = settings->value(SETTING_WWW_ROOT_PATH).toString();

    HttpResponse response;
    if("" == wwwRoot) {
        response = HttpResponse(HttpResponse::NOT_FOUND);
    } else {

        QString uri = req->getRequestUri();

        if(uri == "/") {
            uri = "index.html";
        }

        response = HttpResponse(wwwRoot + uri);
    }
    return response;
}
