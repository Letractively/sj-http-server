/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <QString>
#include <QVector>

class HttpHeader
{
public:
    static const QString CONTENT_TYPE;
    static const QString ACCEPT_CHARSET;
    static const QString CONTENT_DISPOSITION;
    static const QString CONTENT_LENGTH;


    static QString getHeaderValue(const QString & headerName, const QVector<HttpHeader> & headers);

    HttpHeader();
    HttpHeader(const QString & name, const QString & value);
    HttpHeader(const QString & line);
    QString toString();

    QString getName() const { return name; }
    QString getValue() const {return value; }

private:
    QString name;
    QString value;
};

#endif // HTTPHEADER_H
