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


#ifndef LOGGERCONFFILEPARSEHANDLER_H
#define LOGGERCONFFILEPARSEHANDLER_H

#include <QXmlDefaultHandler>
#include <QString>
#include <QStringList>
#include <QMap>
#include "logger.h"

namespace SJ {


/**
  @brief Class responsible for parsing logger configuration file

  Used as a callback class by SAX parser
  */
class LoggerConfFileParseHandler : public QXmlDefaultHandler
{
public:
    LoggerConfFileParseHandler(QMap<QString, Logger *> & loggers);

    virtual bool startElement(const QString &namespaceURI, const QString &localName,
                              const QString &qName, const QXmlAttributes &atts);
    virtual bool endElement(const QString &namespaceURI, const QString &localName,
                            const QString &qName);
    virtual bool characters(const QString &ch);

    virtual bool error ( const QXmlParseException & exception );
    virtual QString	errorString () const;
    virtual bool fatalError ( const QXmlParseException & exception );
    virtual bool warning ( const QXmlParseException & exception );

private: //methods
    bool handleParseException(const QXmlParseException & exception );
    void setAppenderProperty(const QString & name, const QString & value);
    void resetCurrentVariables();

private: //fields
    Logger * currentLogger;
    QString currentLoggerName;
    AbstractAppender * currentAppender;
    QString currentAppenderType;
    QString currentPropertyName;


    QMap<QString, Logger *> & loggers;
    QString errorInfo;

    QStringList supportedLogLevels;

    //   type      parameters
    QMap<QString, QStringList> supportedAppenders;

private: // constants;
    static const QString NS;
    static const QString ELEMENT_LOGGERS;
    static const QString ELEMENT_LOGGER;
    static const QString ELEMENT_APPENDERS;
    static const QString ELEMENT_APPENDER;
    static const QString ELEMENT_APPENDER_PARAM;
    static const QString ATTRIBUTE_LOGGER_NAME;
    static const QString ATTRIBUTE_LOGGER_LEVEL;
    static const QString ATTRIBUTE_APPENDER_TYPE;
    static const QString ATTRIBUTE_APPENDER_PARAM_NAME;

private: //state machine
    enum State {STATE_IDLE, STATE_LOGGERS, STATE_LOGGER, STATE_APPENDERS, STATE_APPENDER,
                STATE_APPENDER_PARAM, STATE_DONE};
    State state;

    bool processStateStartLogger(const QXmlAttributes &atts);
    bool processStateStartAppender(const QXmlAttributes &atts);
    bool processStateStartAppenderParam(const QXmlAttributes &atts);
    bool processStateEndLogger();
    bool processStateEndAppender();
};

} //namespace SJ

#endif // LOGGERCONFFILEPARSEHANDLER_H
