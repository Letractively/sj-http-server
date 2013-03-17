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


#include "imageviewwebhandler.h"
#include "imagegalleryconstants.h"

namespace SJ {

ImageViewWebHandler::ImageViewWebHandler()
{
}

void ImageViewWebHandler::handle(HttpRequest * request, HttpResponse * response, QSettings::SettingsMap *settings) const
{
    QString imagePath = settings->value(ImgGal::SETTING_TMP_DIR).toString() +  request->getParameter(ImgGal::FILE_ID_PARAM);
    response->fromFile(imagePath);
}


} //namespace SJ
