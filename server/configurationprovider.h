

#ifndef CONFIGURATIONPROVIDER_H
#define CONFIGURATIONPROVIDER_H

#include <QString>
#include <QList>
#include <QHostAddress>
#include "handlerconfiguration.h"

namespace SJ {

class ConfigurationProvider
{
public:
    QHostAddress getListenInterface() const;
    int getListenPort() const;
    QString getWwwPath() const;
    QList<HandlerConfiguration> getHandlers() const;

protected:
    ConfigurationProvider();
    QHostAddress listenInterface;
    int listenPort;
    QString wwwPath;
    QList<HandlerConfiguration> handlers;
};


}
#endif // CONFIGURATIONPROVIDER_H
