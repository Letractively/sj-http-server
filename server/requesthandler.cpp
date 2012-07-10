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
#include "httpresponseimpl.h"

namespace SJ {

RequestHandler::RequestHandler()
{
    WWW_ROOT_PATH = Utils::substring(ServerSettings::SETTING_WWW_ROOT_PATH, name().length() + 1);
}

void RequestHandler::handle(HttpRequest * request, HttpResponse * response, QSettings::SettingsMap *settings) const
{
    if(request->getMethod() != HttpRequest::GET) {
        response->setStatusCode(HttpResponse::NOT_FOUND);
        return;
    }

    QString wwwRoot = settings->value(WWW_ROOT_PATH).toString();

    if("" == wwwRoot) {
        response->setStatusCode(HttpResponse::NOT_FOUND);
        return;
    }

    HttpResponseImpl * resImpl = dynamic_cast<HttpResponseImpl*>(response);
    if(!resImpl) {
        //should never happen
        response->setStatusCode(HttpResponse::NOT_FOUND);
        return;
    }

    QString uri = request->getRequestUri();

    if(uri == "/") {
        uri = "index.html";
    }
    resImpl->fromFile(wwwRoot + uri);
}

} // namespace SJ
