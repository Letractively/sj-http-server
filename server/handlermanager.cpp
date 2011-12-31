#include "handlermanager.h"
#include "requesthandler.h"

#include <QPluginLoader>

HandlerManager::HandlerManager()
{
    defaultHandler = new RequestHandler;
    AbstractRequestHandler * fortuneHandler = 0;


    QPluginLoader pl("/home/kuba/image-server/build/fortune-teller/libfortune-teller.so");
    pl.load();
    qDebug() << "fortune teller loaded " << pl.isLoaded();
    if(pl.isLoaded()) {
        qDebug() << "creating instance ...";
        fortuneHandler = qobject_cast<AbstractRequestHandler *>(pl.instance());
        qDebug() << "instance created";
        qDebug() << "name " << fortuneHandler->name();
    }

    if(fortuneHandler !=0 ) {
        handlers.push_back(HandlerData("fortune-cookie", fortuneHandler));
    }
}

HandlerManager::~HandlerManager()
{
    delete defaultHandler;
}

HandlerManager & HandlerManager::instance()
{
    static HandlerManager mgr;
    return mgr;
}

AbstractRequestHandler * HandlerManager::getHandler(HttpRequest * request)
{
    QString uri = request->getRequestUri();

    for(int i = 0; i < handlers.size(); ++i) {
        if(uri.startsWith(handlers[i].getContextPath())) {
            return handlers[i].getHandler();
        }
    }

    return defaultHandler;
}

//    if("/fortune-teller" == request->getRequestUri()) {
//        QPluginLoader pl("/home/kuba/image-server/build/fortune-teller/libfortune-teller.so");
//        pl.load();
//        qDebug() << "fortune teller loaded " << pl.isLoaded();
//        if(pl.isLoaded()) {
//            qDebug() << "creating instance ...";
//            AbstractRequestHandler * handler = qobject_cast<AbstractRequestHandler *>(pl.instance());
//            qDebug() << "instance created";
//            qDebug() << "name " << handler->name();
//            HttpResponse resp = handler->handle(0,0);
//            qDebug() << "req handled ";
//            resp.writeToSocket(socket);
//            socket->disconnectFromHost();
//            return;
//        }
//    }
