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

#include "mockconfigurationprovider.h"

namespace SJ {

MockConfigurationProvider::MockConfigurationProvider()
{
    listenInterface = QHostAddress::LocalHost;
    listenPort = 9090;
    wwwPath = "../www/";

    HandlerConfiguration ft("Fortune Teller",
                            "Presents a random Fortune Cookie Quote",
                            "fortune-cookie",
                            "../fortune-teller/libfortune-teller.so",
                            QMap<QString, QVariant>());
    handlers.push_back(ft);
}

}
