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


#ifndef MAINPAGEWEBHANDLER_H
#define MAINPAGEWEBHANDLER_H

#include "abstractwebhandler.h"
#include "loggerall.h"
#include <QSettings>

namespace SJ {

class MainPageWebHandler : public AbstractWebHandler
{
public:
    MainPageWebHandler();
    void handleGet(HttpRequest * request, HttpResponse * response) const;

private:
    static const Logger & logger;

};

} //namespace SJ

#endif // MAINPAGEWEBHANDLER_H
