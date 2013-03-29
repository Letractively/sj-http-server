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


#include "requesthandler.h"
#include "settingsconstants.h"
#include "serverutils.h"
#include "httpresponseimpl.h"

namespace SJ {

RequestHandler::RequestHandler()
{
//    WWW_ROOT_PATH = Utils::substring(ServerSettings::SETTING_WWW_ROOT_PATH, name().length() + 1);
    WWW_ROOT_PATH = "../www/";
}

void RequestHandler::init(QMap<QString, QVariant> & /*initParams*/)
{
    //TODO
//    WWW_ROOT_PATH = "../www/";
}

void RequestHandler::handle(HttpRequest * request, HttpResponse * response) const
{
    if(request->getMethod() != HttpRequest::GET) {
        response->setStatusCode(HttpResponse::SC_NOT_FOUND);
        return;
    }


    if("" == WWW_ROOT_PATH) {
        response->setStatusCode(HttpResponse::SC_NOT_FOUND);
        return;
    }

    QString uri = request->getRequestUri();

    if(uri == "/") {
        uri = "index.html";
    }
    response->fromFile(WWW_ROOT_PATH + uri);
}

} // namespace SJ
