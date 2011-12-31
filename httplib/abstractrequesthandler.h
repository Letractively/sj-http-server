#ifndef ABSTRACTREQUESTHANDLER_H
#define ABSTRACTREQUESTHANDLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "settingsitem.h"

#include <QVector>
#include <QSettings>
#include <QtPlugin>

class AbstractRequestHandler
{
public:
    virtual ~AbstractRequestHandler() {}
    virtual QString name() = 0;
    virtual QString description() {return ""; }
    virtual QString helpInfo() {return ""; }
    virtual HttpResponse handle(HttpRequest * req, QSettings * settings = 0) = 0;
    virtual QVector<SettingsItem> supportedSettings() {return QVector<SettingsItem>(0); }
};

Q_DECLARE_INTERFACE(AbstractRequestHandler, "kuba.image-server.AbstractRequestHandler/0.1")

#endif // ABSTRACTREQUESTHANDLER_H
