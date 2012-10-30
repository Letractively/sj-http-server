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
#include "loggerall.h"
#include "imagemetadataprovider.h"

namespace SJ {

const Logger & MainPageWebHandler::logger = LoggerFactory::instance().getLogger("sj-image-gallery-logger");

MainPageWebHandler::MainPageWebHandler()
{
}


void MainPageWebHandler::handle(HttpRequest * request, HttpResponse * response, QSettings::SettingsMap * /*settings*/) const
{
    QString uploadLink = request->getRequestUri();
    uploadLink += (uploadLink.endsWith("/") ? "upload" : "/upload");

    QByteArray resp;
    resp.append("<html><body>Welcome to image gallery<br><br>");
    resp.append("To upload a new image go to <a href=\"");
    resp.append(uploadLink);
    resp.append("\">upload page</a><br><br>Currently there are the following images:");

    QList<ImageMetadata> images = ImageMetadataProvider::getInstance()->getImages();
    for(int i = 0; i < images.size(); ++i) {
        ImageMetadata img = images.at(i);
        LOG_DEBUG(logger, (LogBuilder("image #").append(i).append(": ").append(img.toString())));
        resp.append("<br><a href=\"show?file=" + img.getFilename() + "\">" + img.getTitle() + "</a> by " + img.getAuthor());
    }


    resp.append("</body></html>");
    response->writeData(resp);


}

} //namespace SJ
