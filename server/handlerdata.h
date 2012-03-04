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


#ifndef HANDLERDATA_H
#define HANDLERDATA_H

#include <QString>
#include "abstractrequesthandler.h"

class HandlerData
{
public:
    HandlerData();
    HandlerData(const QString & contextRoot, AbstractRequestHandler * handler, const QString & settingsGroup = "");
    ~HandlerData();
    QString getContextRoot() const { return contextRoot; }
    AbstractRequestHandler * getHandler() const {return handler;}
    QString getSettingsGroup() { return settingsGroup; }
    void setContextRoot(const QString & contextRoot) { this->contextRoot = contextRoot; }
private:
    QString contextRoot;
    AbstractRequestHandler * handler;
    QString settingsGroup;
};

#endif // HANDLERDATA_H
