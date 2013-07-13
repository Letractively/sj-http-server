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


#include "abstractwebhandler.h"

namespace SJ {

AbstractWebHandler::AbstractWebHandler()
{

}

void AbstractWebHandler::handleGet(HttpRequest *request, HttpResponse *response) const
{
    internaHandle(request, response);
}

void AbstractWebHandler::handlePost(HttpRequest *request, HttpResponse *response) const
{
    internaHandle(request, response);
}

void AbstractWebHandler::internaHandle(HttpRequest * /*request */, HttpResponse *response) const
{
    response->setStatusCode(HttpResponse::StatusCode::SC_METHOD_NOT_ALLOWED);
    QByteArray data("This method is not supported");
    response->writeData(data);
}

} //namespace SJ
