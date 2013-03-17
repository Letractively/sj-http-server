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


#include "loggerconffileparsehandler.h"
#include "consoleappender.h"
#include "fileappender.h"

#include <QDebug>

namespace SJ {

const QString LoggerConfFileParseHandler::NS = "http://sj-http-server.googlecode.com/logger";
const QString LoggerConfFileParseHandler::ELEMENT_LOGGERS = "loggers";
const QString LoggerConfFileParseHandler::ELEMENT_LOGGER = "logger";
const QString LoggerConfFileParseHandler::ELEMENT_APPENDERS = "appenders";
const QString LoggerConfFileParseHandler::ELEMENT_APPENDER = "appender";
const QString LoggerConfFileParseHandler::ELEMENT_APPENDER_PARAM = "appenderParam";
const QString LoggerConfFileParseHandler::ATTRIBUTE_LOGGER_NAME = "name";
const QString LoggerConfFileParseHandler::ATTRIBUTE_LOGGER_LEVEL = "level";
const QString LoggerConfFileParseHandler::ATTRIBUTE_APPENDER_TYPE = "type";
const QString LoggerConfFileParseHandler::ATTRIBUTE_APPENDER_PARAM_NAME = "name";


LoggerConfFileParseHandler::LoggerConfFileParseHandler(QMap<QString, Logger *> & loggers)
    : loggers(loggers),
      errorInfo(""),
      state(STATE_IDLE)
{
    resetCurrentVariables();
    //supportedLogLevels
    //iterating over an enum - yes, I know what I'm doing :-)
    for(int i = (int) LoggingLevel::ALL + 1; i < (int) LoggingLevel::NONE; ++i) {
        supportedLogLevels.append(LoggingLevel::levelToString(
                                      (LoggingLevel::Level) ((int) LoggingLevel::ALL + i)
                                      ));
    }

    //supportedAppenders
    supportedAppenders.insert(ConsoleAppender::type(), ConsoleAppender::supportedParams());
    supportedAppenders.insert(FileAppender::type(), FileAppender::supportedParams());

}

QString LoggerConfFileParseHandler::errorString() const
{
    return errorInfo;
}

bool LoggerConfFileParseHandler::startElement(const QString &namespaceURI, const QString &localName,
                                              const QString &/*qName*/, const QXmlAttributes &atts)
{
    if(namespaceURI != NS) {
        errorInfo = "expected namespace is [" + NS + "] but got [" + namespaceURI + "]";
        return false;
    }

    switch(state) {
    case STATE_IDLE:
        if(localName == ELEMENT_LOGGERS) {
            state = STATE_LOGGERS;
        } else {
            errorInfo = "expected [" + ELEMENT_LOGGERS + "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_LOGGERS:
        if(localName == ELEMENT_LOGGER) {
            state = STATE_LOGGER;
            return processStateStartLogger(atts);
        } else {
            errorInfo = "expected [" + ELEMENT_LOGGER + "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_LOGGER:
        if(localName == ELEMENT_APPENDERS) {
            state = STATE_APPENDERS;
        } else {
            errorInfo = "expected [" + ELEMENT_APPENDERS + "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_APPENDERS:
        if(localName == ELEMENT_APPENDER) {
            state = STATE_APPENDER;
            return processStateStartAppender(atts);
        } else {
            errorInfo = "expected [" + ELEMENT_APPENDER + "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_APPENDER:
        if(localName == ELEMENT_APPENDER_PARAM) {
            state = STATE_APPENDER_PARAM;
            return processStateStartAppenderParam(atts);
        } else {
            errorInfo = "expected [" + ELEMENT_APPENDER_PARAM + "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_APPENDER_PARAM:
    case STATE_DONE:
        errorInfo = "unexpected start of element [" + localName + "]";
        return false;
    }
    return true;
}

bool LoggerConfFileParseHandler::endElement(const QString &namespaceURI,
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
    case STATE_APPENDER_PARAM:
        if(localName == ELEMENT_APPENDER_PARAM) {
            state = STATE_APPENDER;
        } else {
            errorInfo = "expected [" + ELEMENT_APPENDER_PARAM + "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_APPENDER:
        if(localName == ELEMENT_APPENDER) {
            state = STATE_APPENDERS;
            return processStateEndAppender();
        } else {
            errorInfo = "expected [" + ELEMENT_APPENDER + "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_APPENDERS:
        if(localName == ELEMENT_APPENDERS) {
            state = STATE_LOGGER;
        } else {
            errorInfo = "expected [" + ELEMENT_APPENDERS + "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_LOGGER:
        if(localName == ELEMENT_LOGGER) {
            state = STATE_LOGGERS;
            processStateEndLogger();
        } else {
            errorInfo = "expected [" + ELEMENT_LOGGER+ "]  but got [" + localName + "]";
            return false;
        }
        break;
    case STATE_LOGGERS:
        if(localName == ELEMENT_LOGGERS) {
            state = STATE_DONE;
        }  else {
            errorInfo = "expected [" + ELEMENT_LOGGERS + "]  but got [" + localName + "]";
            return false;
        }
        break;
    }

    return true;
}

bool LoggerConfFileParseHandler::characters(const QString &ch)
{
    QString chtrimmed = ch.trimmed();
    switch(state) {
    case STATE_APPENDER_PARAM:
        //value of a parameter
        setAppenderProperty(currentPropertyName, ch);
        break;
    default:
        if(!chtrimmed.isEmpty()) {
            errorInfo = "unexpected characters: [" + chtrimmed + "]";
            return false;
        }
    }
    return true;
}



bool LoggerConfFileParseHandler::processStateStartLogger(const QXmlAttributes &atts)
{
    currentLoggerName = atts.value("", ATTRIBUTE_LOGGER_NAME);
    QString logLevel = atts.value("", ATTRIBUTE_LOGGER_LEVEL);

    if(currentLoggerName.isEmpty()) {
        errorInfo = "logger name cannot be empty";
        return false;
    }

    if(!supportedLogLevels.contains(logLevel)) {
        errorInfo = "unsupported logging level [" + logLevel + "] specified";
        return false;
    }
    LoggingLevel::Level level = LoggingLevel::stringToLevel(logLevel);

    currentLogger = new Logger();
    currentLogger->setLevel(level);

    return true;
}

bool LoggerConfFileParseHandler::processStateStartAppender(const QXmlAttributes &atts)
{
    currentAppenderType = atts.value("", ATTRIBUTE_APPENDER_TYPE);

    if(currentAppenderType == ConsoleAppender::type()) {
        currentAppender = new ConsoleAppender();
    } else if (currentAppenderType == FileAppender::type()) {
        currentAppender = new FileAppender();
    } else {
        errorInfo = "unsupported appender type specified: [" + currentAppenderType + "]";
        return false;
    }

    return true;
}

bool LoggerConfFileParseHandler::processStateStartAppenderParam(const QXmlAttributes &atts)
{
    currentPropertyName = atts.value("", ATTRIBUTE_APPENDER_PARAM_NAME);
    return true;
}

bool LoggerConfFileParseHandler::processStateEndLogger()
{
    loggers.insert(currentLoggerName, currentLogger);
    resetCurrentVariables();
    return true;
}

bool LoggerConfFileParseHandler::processStateEndAppender()
{
    currentLogger->addAppender(currentAppender, true);
    return true;
}

void LoggerConfFileParseHandler::resetCurrentVariables()
{
    currentLogger = 0;
    currentLoggerName = "";
    currentAppender = 0;
    currentAppenderType = "";
    currentPropertyName = "";
}

void LoggerConfFileParseHandler::setAppenderProperty(const QString &name, const QString &value)
{
    if(supportedAppenders.contains(currentAppenderType)) {
        QStringList supportedParams = supportedAppenders.value(currentAppenderType);
        if(supportedParams.contains(name)) {
            bool success = currentAppender->setProperty(name, value);
            if(success) {
                return;
            }
        }
    }

    qWarning() << "Unable to set property '" + name + "'' to appender of type [" + currentAppenderType + "]";
}

bool LoggerConfFileParseHandler::error ( const QXmlParseException & exception )
{
    return handleParseException(exception);
}

bool LoggerConfFileParseHandler::fatalError ( const QXmlParseException & exception )
{
    return handleParseException(exception);
}

bool LoggerConfFileParseHandler::warning ( const QXmlParseException & exception )
{
    return handleParseException(exception);
}

bool LoggerConfFileParseHandler::handleParseException(const QXmlParseException & exception)
{
    qWarning() << "Exception while parsing xml file: " + exception.message();
    errorInfo = exception.message() + " at line:column ["
            + QString::number(exception.lineNumber()) + ":" + QString::number(exception.columnNumber()) + "]";
    return false;
}


} //namespace SJ
