/*
http://sj-http-server.googlecode.com/

Copyright (C) Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef XMLCONFIGURATIONPROVIDER_H
#define XMLCONFIGURATIONPROVIDER_H

#include "configurationprovider.h"
#include "loggerall.h"
#include <QXmlDefaultHandler>

namespace SJ {

class XmlConfigurationParser;

class XmlConfigurationProvider : public ConfigurationProvider
{
public:
    XmlConfigurationProvider();
    XmlConfigurationProvider(const QString & configFile);
    virtual bool loaded() const;
private:
    void doParse(const QString & configFile);
    bool configLoaded;

    friend class XmlConfigurationParser;
};

class XmlConfigurationParser : public QXmlDefaultHandler
{
public:
    XmlConfigurationParser(XmlConfigurationProvider * provider);

    virtual bool startElement(const QString &namespaceURI, const QString &localName,
                              const QString &qName, const QXmlAttributes &atts);
    virtual bool endElement(const QString &namespaceURI, const QString &localName,
                            const QString &qName);
    virtual bool characters(const QString &ch);

    virtual bool error ( const QXmlParseException & exception );
    virtual QString	errorString () const;
    virtual bool fatalError ( const QXmlParseException & exception );
    virtual bool warning ( const QXmlParseException & exception );


private:
    XmlConfigurationProvider * provider;

private: //methods
    bool handleParseException(const QXmlParseException & exception );
    void resetCurrentVariables();

private: //fields
    QString chars;
    QString errorInfo;
    static Logger & logger;

    QString currentHandlerName;
    QString currentHandlerDescription;
    QString currentHandlerContextRoot;
    QString currentHandlerFilePath;
    QMap<QString, QVariant> currentParams;
    QString currentParamName;

private: // constants;
    static const QString NS;
    static const QString ELEMENT_SERVER_CONF;
    static const QString ELEMENT_LISTEN_INTERFACE;
    static const QString ELEMENT_LISTEN_PORT;
    static const QString ELEMENT_WWW_PATH;
    static const QString ELEMENT_HANDLERS;
    static const QString ELEMENT_HANDLER;
    static const QString ELEMENT_HANDLER_NAME;
    static const QString ELEMENT_HANDLER_DESCRIPTION;
    static const QString ELEMENT_HANDLER_CONTEXT_ROOT;
    static const QString ELEMENT_HANDLER_FILE_PATH;
    static const QString ELEMENT_HANDLER_PARAMS;
    static const QString ELEMENT_HANDLER_PARAM;
    static const QString ELEMENT_HANDLER_PARAM_NAME;
    static const QString ELEMENT_HANDLER_PARAM_VALUE;

private: // state machine
    enum class State {STATE_IDLE,
                STATE_SERVER_CONF,
                STATE_LISTEN_INTERFACE,
                STATE_LISTEN_INTERFACE_DONE,
                STATE_LISTEN_PORT,
                STATE_LISTEN_PORT_DONE,
                STATE_WWW_PATH,
                STATE_WWW_PATH_DONE,
                STATE_HANDLERS,
                STATE_HANDLERS_DONE,
                STATE_HANDLER,
                STATE_HANDLER_DONE,
                STATE_HANDLER_NAME,
                STATE_HANDLER_NAME_DONE,
                STATE_HANDLER_DESCRIPTION,
                STATE_HANDLER_DESCRIPTION_DONE,
                STATE_HANDLER_CONTEXT_ROOT,
                STATE_HANDLER_CONTEXT_ROOT_DONE,
                STATE_HANDLER_FILE_PATH,
                STATE_HANDLER_FILE_PATH_DONE,
                STATE_HANDLER_PARAMS,
                STATE_HANDLER_PARAMS_DONE,
                STATE_HANDLER_PARAM,
                STATE_HANDLER_PARAM_DONE,
                STATE_HANDLER_PARAM_NAME,
                STATE_HANDLER_PARAM_NAME_DONE,
                STATE_HANDLER_PARAM_VALUE,
                STATE_HANDLER_PARAM_VALUE_DONE,
                STATE_DONE};
    State state;
};


}

#endif // XMLCONFIGURATIONPROVIDER_H
