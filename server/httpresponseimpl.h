/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

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


#ifndef HTTPRESPONSEIMPL_H
#define HTTPRESPONSEIMPL_H

#include "httpresponse.h"
#include "httpheader.h"
#include "loggerall.h"
#include <QString>
#include <QVector>
#include <QByteArray>
#include <QTcpSocket>
#include <QFile>

namespace SJ {

class HttpResponseImpl : public HttpResponse
{
public:

    HttpResponseImpl(const QString & requestID);
//    HttpResponseImpl(StatusCode code);
//    HttpResponseImpl(QByteArray * data);
//    HttpResponseImpl(QString filePath, QString contentType = "");
    virtual ~HttpResponseImpl();
    virtual void setStatusCode(StatusCode code);
    virtual void setContentType(const QString & contentType);
    virtual void addHeader(QString name, QString value);
    virtual void writeData(const QByteArray & data);


    void writeToSocket(QTcpSocket * socket);
    void fromFile(const QString & filePath);

private:
    static const char * EOL;
    static QString codeToString(StatusCode code);
    static QString guessContentType(QString filePath);
    void setDefaultHeaders();

    static const Logger & logger;

    StatusCode code;
    QVector<HttpHeader> headers;
    QByteArray data;
    QFile * file;
    QString contentType;
    QString requestID;

};

} // namespace SJ


#endif // HTTPRESPONSEIMPL_H
