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

#include "xmlconfigurationprovider.h"

#include <QStringBuilder>
#include <QVariant>

namespace SJ {

const QString XmlConfigurationParser::NS = "http://sj-http-server.googlecode.com/server";
const QString XmlConfigurationParser::ELEMENT_SERVER_CONF = "server-conf";
const QString XmlConfigurationParser::ELEMENT_LISTEN_INTERFACE = "listen-interface";
const QString XmlConfigurationParser::ELEMENT_LISTEN_PORT = "listen-port";
const QString XmlConfigurationParser::ELEMENT_WWW_PATH = "www-path";
const QString XmlConfigurationParser::ELEMENT_HANDLERS = "handlers";
const QString XmlConfigurationParser::ELEMENT_HANDLER = "handler";
const QString XmlConfigurationParser::ELEMENT_HANDLER_NAME = "name";
const QString XmlConfigurationParser::ELEMENT_HANDLER_DESCRIPTION = "description";
const QString XmlConfigurationParser::ELEMENT_HANDLER_CONTEXT_ROOT = "context-root";
const QString XmlConfigurationParser::ELEMENT_HANDLER_FILE_PATH = "file-path";
const QString XmlConfigurationParser::ELEMENT_HANDLER_PARAMS = "init-params";
const QString XmlConfigurationParser::ELEMENT_HANDLER_PARAM = "init-param";
const QString XmlConfigurationParser::ELEMENT_HANDLER_PARAM_NAME = "name";
const QString XmlConfigurationParser::ELEMENT_HANDLER_PARAM_VALUE = "value";

Logger & XmlConfigurationParser::logger = SJ::LoggerFactory::instance().getLogger("sj-server-logger");


XmlConfigurationProvider::XmlConfigurationProvider()
{
    doParse("sj-http-server.xml");
}

XmlConfigurationProvider::XmlConfigurationProvider(const QString & configFile)
{
    doParse(configFile);
}

void XmlConfigurationProvider::doParse(const QString &configFile)
{
    //read settings from a file
    QFile file(configFile);
    if(!file.exists()) {
        LOG_WARN(logger, LogBuilder("File ").append(configFile).append(" not found, server is not configured"));
        return;
    }

    LOG_INFO(logger, LogBuilder("Loading server configuration from file ").append(configFile));

    QXmlInputSource source(&file);
    XmlConfigurationParser handler(this);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);
    configLoaded = reader.parse(source);
}

bool XmlConfigurationProvider::loaded() const {
    return configLoaded;
}

XmlConfigurationParser::XmlConfigurationParser(XmlConfigurationProvider * provider)
    : provider(provider), state(STATE_IDLE)
{
    resetCurrentVariables();
}


bool XmlConfigurationParser::startElement(const QString &namespaceURI, const QString &localName,
                                              const QString &/*qName*/, const QXmlAttributes & /*atts*/)
{
    chars = "";
    if(namespaceURI != NS) {
        errorInfo = "expected namespace is [" + NS + "] but got [" + namespaceURI + "]";
        return false;
    }

    switch(state) {
    case STATE_IDLE:
        if(localName == ELEMENT_SERVER_CONF) {
            state = STATE_SERVER_CONF;
        } else {
            errorInfo = "expected [" + ELEMENT_SERVER_CONF + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_SERVER_CONF:
        if(localName == ELEMENT_LISTEN_INTERFACE) {
            state = STATE_LISTEN_INTERFACE;
        } else {
            errorInfo = "expected [" + ELEMENT_LISTEN_INTERFACE + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_LISTEN_INTERFACE_DONE:
        if(localName == ELEMENT_LISTEN_PORT) {
            state = STATE_LISTEN_PORT;
        } else {
            errorInfo = "expected [" + ELEMENT_LISTEN_PORT + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_LISTEN_PORT_DONE:
        if(localName == ELEMENT_WWW_PATH) {
            state = STATE_WWW_PATH;
        } else {
            errorInfo = "expected [" + ELEMENT_WWW_PATH + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_WWW_PATH_DONE:
        if(localName == ELEMENT_HANDLERS) {
            state = STATE_HANDLERS;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLERS + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLERS:
    case STATE_HANDLER_DONE:
        if(localName == ELEMENT_HANDLER) {
            state = STATE_HANDLER;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER:
        if(localName == ELEMENT_HANDLER_NAME) {
            state = STATE_HANDLER_NAME;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER_NAME + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_NAME_DONE:
        if(localName == ELEMENT_HANDLER_DESCRIPTION) {
            state = STATE_HANDLER_DESCRIPTION;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER_DESCRIPTION + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_DESCRIPTION_DONE:
        if(localName == ELEMENT_HANDLER_CONTEXT_ROOT) {
            state = STATE_HANDLER_CONTEXT_ROOT;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER_CONTEXT_ROOT + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_CONTEXT_ROOT_DONE:
        if(localName == ELEMENT_HANDLER_FILE_PATH) {
            state = STATE_HANDLER_FILE_PATH;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER_FILE_PATH + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_FILE_PATH_DONE:
        if(localName == ELEMENT_HANDLER_PARAMS) {
            state = STATE_HANDLER_PARAMS;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER_PARAMS + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_PARAMS:
    case STATE_HANDLER_PARAM_DONE:
        if(localName == ELEMENT_HANDLER_PARAM) {
            state = STATE_HANDLER_PARAM;
            currentParamName = "";
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER_PARAM + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_PARAM:
        if(localName == ELEMENT_HANDLER_PARAM_NAME) {
            state = STATE_HANDLER_PARAM_NAME;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER_PARAM_NAME + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_PARAM_NAME_DONE:
        if(localName == ELEMENT_HANDLER_PARAM_VALUE) {
            state = STATE_HANDLER_PARAM_VALUE;
        } else {
            errorInfo = "expected [" + ELEMENT_HANDLER_PARAM_VALUE + "]  but got [" + localName + "]";
            return false;
        }
        break;

    default:
        errorInfo = "unexpected start of element [" + localName + "]";
        return false;
        }
    return true;
}

bool XmlConfigurationParser::endElement(const QString &namespaceURI,
                                 const QString &localName, const QString & /* qName */)
{

    if(namespaceURI != NS) {
        errorInfo = "expected namespace is [" + NS + "] but got [" + namespaceURI + "]";
        return false;
    }

    switch(state) {
    case STATE_IDLE:
    case STATE_DONE:
        errorInfo = "unexpected end of element [" + localName + "]";
        return false;

    case STATE_SERVER_CONF:
        if(localName == ELEMENT_SERVER_CONF) {
            state = STATE_DONE;
        } else {
            errorInfo = "expected end of [" + ELEMENT_SERVER_CONF + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_LISTEN_INTERFACE:
        if(localName == ELEMENT_LISTEN_INTERFACE) {
            state = STATE_LISTEN_INTERFACE_DONE;
            QHostAddress host;
            if(chars == "any") {
                host = QHostAddress::Any;
            } else if(chars == "localhost" || chars == "127.0.0.1") {
                host = QHostAddress::LocalHost;
            } else {
                bool ok = host.setAddress(chars);
                if(!ok) {
                    errorInfo = "unable to parse address [" + chars + "]";
                    return false;
                }
            }
            provider->listenInterface = host;
        } else {
            errorInfo = "expected end of [" + ELEMENT_LISTEN_INTERFACE + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_LISTEN_PORT:
        if(localName == ELEMENT_LISTEN_PORT) {
            state = STATE_LISTEN_PORT_DONE;
            QVariant v(chars);
            bool ok = false;
            provider->listenPort=v.toInt(&ok);
            if(!ok) {
                errorInfo = "Unable to set port to [" + chars + "]";
                return false;
            }
        } else {
            errorInfo = "expected end of [" + ELEMENT_LISTEN_PORT + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_WWW_PATH:
        if(localName == ELEMENT_WWW_PATH) {
            state = STATE_WWW_PATH_DONE;
            provider->wwwPath = chars;
        } else {
            errorInfo = "expected end of [" + ELEMENT_WWW_PATH + "]  but got [" + localName + "]";
            return false;
        }
        break;

    case STATE_WWW_PATH_DONE:
        if(localName == ELEMENT_SERVER_CONF) {
            state = STATE_DONE;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_NAME:
        if(localName == ELEMENT_HANDLER_NAME) {
            state = STATE_HANDLER_NAME_DONE;
            currentHandlerName = chars;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_DESCRIPTION:
        if(localName == ELEMENT_HANDLER_DESCRIPTION) {
            state = STATE_HANDLER_DESCRIPTION_DONE;
            currentHandlerDescription = chars;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_CONTEXT_ROOT:
        if(localName == ELEMENT_HANDLER_CONTEXT_ROOT) {
            state = STATE_HANDLER_CONTEXT_ROOT_DONE;
            currentHandlerContextRoot = chars;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_FILE_PATH:
        if(localName == ELEMENT_HANDLER_FILE_PATH) {
            state = STATE_HANDLER_FILE_PATH_DONE;
            currentHandlerFilePath = chars;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_FILE_PATH_DONE:
        if(localName == ELEMENT_HANDLER) {
            state = STATE_HANDLER_DONE;
            HandlerConfiguration handler = HandlerConfiguration(currentHandlerName, currentHandlerDescription,
                                                                currentHandlerContextRoot, currentHandlerFilePath,
                                                                currentParams);
            provider->handlers.push_back(handler);
            resetCurrentVariables();
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_DONE:
        if(localName == ELEMENT_HANDLERS) {
            state = STATE_HANDLERS_DONE;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLERS_DONE:
        if(localName == ELEMENT_SERVER_CONF) {
            state = STATE_DONE;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_PARAM_NAME:
        if(localName == ELEMENT_HANDLER_PARAM_NAME) {
            state = STATE_HANDLER_PARAM_NAME_DONE;
            currentParamName = chars;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_PARAM_VALUE:
        if(localName == ELEMENT_HANDLER_PARAM_VALUE) {
            state = STATE_HANDLER_PARAM_VALUE_DONE;
            currentParams.insert(currentParamName, QVariant(chars));
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_PARAM_VALUE_DONE:
        if(localName == ELEMENT_HANDLER_PARAM) {
            state = STATE_HANDLER_PARAM_DONE;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_PARAM_DONE:
        if(localName == ELEMENT_HANDLER_PARAMS) {
            state = STATE_HANDLER_PARAMS_DONE;
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    case STATE_HANDLER_PARAMS_DONE:
        if(localName == ELEMENT_HANDLER) {
            state = STATE_HANDLER_DONE;
            HandlerConfiguration handler = HandlerConfiguration(currentHandlerName, currentHandlerDescription,
                                                                currentHandlerContextRoot, currentHandlerFilePath,
                                                                currentParams);
            provider->handlers.push_back(handler);
        } else {
            errorInfo = "unexpected end of [" + localName + "]";
            return false;
        }
        break;

    default:
        errorInfo = "unexpected end of element [" + localName + "]";
        return false;
    }
    return true;
}

bool XmlConfigurationParser::characters(const QString &ch)
{
    switch(state) {
    case STATE_LISTEN_INTERFACE:
    case STATE_LISTEN_PORT:
    case STATE_WWW_PATH:
    case STATE_HANDLER_NAME:
    case STATE_HANDLER_DESCRIPTION:
    case STATE_HANDLER_CONTEXT_ROOT:
    case STATE_HANDLER_FILE_PATH:
    case STATE_HANDLER_PARAM_NAME:
    case STATE_HANDLER_PARAM_VALUE:
        //buffer characters ('%' works as '+', but better)
        chars = chars % ch;
        break;
    default:
        QString chtrimmed = ch.trimmed();
        if(!chtrimmed.isEmpty()) {
            errorInfo = "unexpected characters: [" + chtrimmed + "]";
            return false;
        }
    }
    return true;
}

void XmlConfigurationParser::resetCurrentVariables()
{
    currentHandlerName = "";
    currentHandlerDescription = "";
    currentHandlerContextRoot = "";
    currentHandlerFilePath = "";
    currentParams.clear();
    currentParamName = "";
}

bool XmlConfigurationParser::error ( const QXmlParseException & exception )
{
    return handleParseException(exception);
}

bool XmlConfigurationParser::fatalError ( const QXmlParseException & exception )
{
    return handleParseException(exception);
}

bool XmlConfigurationParser::warning ( const QXmlParseException & exception )
{
    return handleParseException(exception);
}

bool XmlConfigurationParser::handleParseException(const QXmlParseException & exception)
{
    errorInfo = exception.message() + " at line:column ["
            + QString::number(exception.lineNumber()) + ":" + QString::number(exception.columnNumber()) + "]";
    LOG_ERROR(logger, LogBuilder("Exception while parsing xml file: ").append(errorInfo));
    return false;
}

QString XmlConfigurationParser::errorString() const
{
    return errorInfo;
}

}
