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
#include "httpresponseimpl.h"
#include "configurationprovider.h"

namespace SJ {

RequestHandler::RequestHandler()
{
    WWW_ROOT_PATH = ConfigurationProvider::getInstance()->getWwwPath();
}

void RequestHandler::init(QMap<QString, QVariant> & /*initParams*/)
{

}

void RequestHandler::handle(HttpRequest * request, HttpResponse * response) const
{
    if(request->getMethod() != HttpRequest::RequestMethod::GET) {
        response->setStatusCode(HttpResponse::StatusCode::SC_NOT_FOUND);
        return;
    }


    if("" == WWW_ROOT_PATH) {
        response->setStatusCode(HttpResponse::StatusCode::SC_NOT_FOUND);
        return;
    }

    QString uri = request->getRequestUri();

    if(uri == "/") {
        uri = "index.html";
    }
    response->fromFile(WWW_ROOT_PATH + uri);
}

} // namespace SJ
