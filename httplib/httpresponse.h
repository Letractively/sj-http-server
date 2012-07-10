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


#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QString>
#include <QByteArray>

namespace SJ {

class HttpResponse
{
public:

    enum StatusCode {OK = 200, NOT_FOUND = 404};

    HttpResponse() {}
    virtual ~HttpResponse() {}
    virtual void setStatusCode(StatusCode code) = 0;
    virtual void addHeader(QString name, QString value) = 0;
    virtual void setContentType(const QString & contentType) = 0;
    virtual void writeData(const QByteArray & data) = 0;
    virtual void fromFile(const QString & filePath) = 0;
};

} // namespace SJ

#endif // HTTPRESPONSE_H
