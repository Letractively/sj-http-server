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


#include "httpheader.h"

namespace SJ {

const QString HttpHeader::CONTENT_TYPE = "Content-Type";
const QString HttpHeader::ACCEPT_CHARSET = "Accept-Charset";
const QString HttpHeader::CONTENT_DISPOSITION = "Content-Disposition";
const QString HttpHeader::CONTENT_LENGTH = "Content-Length";

HttpHeader::HttpHeader()
    : name(""), value("")
{

}

QString HttpHeader::getHeaderValue(const QString & headerName, const QVector<HttpHeader> & headers)
{
    for(int i = 0; i < headers.size(); i++) {
        if(headers[i].getName() == headerName)
        {
            return headers[i].getValue();
        }
    }
    return "";
}

QVector<QString> HttpHeader::getHeaderValues(const QString & headerName, const QVector<HttpHeader> & headers)
{
    QVector<QString> vect;
    for(int i = 0; i < headers.size(); i++) {
        if(headers[i].getName() == headerName)
        {
            vect.push_back(headers[i].getValue());
        }
    }
    return vect;
}

HttpHeader::HttpHeader(const QString & name, const QString & value)
    : name(name), value(value)
{
}

HttpHeader::HttpHeader(const QString & line)
{
    name = line.left(line.indexOf(':'));
    value = line.right(line.length() - line.indexOf(':') - 1).trimmed();
}


QString HttpHeader::toString() {
    return name + ": " + value;
}

} //namespace SJ
