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


#include "mainpagewebhandler.h"
namespace SJ {

MainPageWebHandler::MainPageWebHandler()
{
}


void MainPageWebHandler::handle(HttpRequest * /*request*/, HttpResponse * response, QSettings::SettingsMap * /*settings*/) const
{
    QByteArray resp;
    resp.append("<html><body>Welcome to image gallery<br><br>"
                "To upload a new image go to <a href=\"upload\">upload page</a><br>"
                    "</body></html>");
    response->writeData(resp);
}

} //namespace SJ
