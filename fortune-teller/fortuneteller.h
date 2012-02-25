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


#ifndef FORTUNETELLER_H
#define FORTUNETELLER_H

#include <abstractrequesthandler.h>
#include <QObject>
#include <QVector>

/**
 * @brief Application prints a random fortune cookie quote
 */
class FortuneTeller : public QObject, public AbstractRequestHandler
{
    Q_OBJECT
    Q_INTERFACES(AbstractRequestHandler)
public:
    QString name() const;
    HttpResponse handle(HttpRequest *req, QSettings *settings) const;
private:
    static QVector<QString> fortunes;
    static bool fortunesSet;
    static QString getFortune();
};

#endif // FORTUNETELLER_H
