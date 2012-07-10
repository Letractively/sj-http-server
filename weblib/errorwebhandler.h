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


#ifndef ERRORWEBHANDLER_H
#define ERRORWEBHANDLER_H


#include "abstractwebhandler.h"
#include "httprequest.h"
#include "httpresponse.h"

namespace SJ {
class ErrorWebHandler : public AbstractWebHandler
{
public:
    ErrorWebHandler();
    ~ErrorWebHandler();
    void handle(HttpRequest * request, HttpResponse *response, QSettings::SettingsMap * = 0) const;

};

} //namespace SJ

#endif // ERRORWEBHANDLER_H
