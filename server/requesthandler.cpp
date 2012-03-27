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


#include "requesthandler.h"
#include "settingsconstants.h"
#include "serverutils.h"

RequestHandler::RequestHandler()
{
    WWW_ROOT_PATH = Utils::substring(ServerSettings::SETTING_WWW_ROOT_PATH, name().length() + 1);
}

HttpResponse RequestHandler::handle(HttpRequest *req, QSettings::SettingsMap *settings) const
{
    if(req->getMethod() != HttpRequest::GET) {
        return HttpResponse(HttpResponse::NOT_FOUND);
    }

    QString wwwRoot = settings->value(WWW_ROOT_PATH).toString();

    HttpResponse response;
    if("" == wwwRoot) {
        response = HttpResponse(HttpResponse::NOT_FOUND);
    } else {

        QString uri = req->getRequestUri();

        if(uri == "/") {
            uri = "index.html";
        }

        response = HttpResponse(wwwRoot + uri);
    }
    return response;
}
