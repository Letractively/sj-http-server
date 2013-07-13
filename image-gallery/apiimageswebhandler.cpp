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


#include "apiimageswebhandler.h"
#include "imagemetadataprovider.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
namespace SJ {

ApiImagesWebHandler::ApiImagesWebHandler(const QString & context)
    : contextRoot(context)
{

}

void ApiImagesWebHandler::handleGet(HttpRequest * request, HttpResponse *response) const
{
    QList<ImageMetadata> images = ImageMetadataProvider::getInstance()->getImages();
    QJsonArray json;

    foreach(const ImageMetadata& image, images) {
        QJsonObject jo;
        jo.insert("filename", QJsonValue(image.getFilename()));
        jo.insert("author", QJsonValue(image.getAuthor()));
        jo.insert("title", QJsonValue(image.getTitle()));
        jo.insert("uploadDate", QJsonValue(image.getUploadDate().toString(Qt::DateFormat::ISODate)));
        QString uri = request->getRequestUrl().left(request->getRequestUrl().length()
                                                    - request->getRequestUri().length());
        uri += "/" + contextRoot + "/show?file=" + image.getFilename();
        jo.insert("uri", QJsonValue(uri));
        jo.insert("originalFilename", QJsonValue(image.getOriginalFilename()));
        json.append(QJsonValue(jo));
    }

    response->setContentType("application/json");
    response->writeData(QJsonDocument(json).toJson());
}

//void ApiImagesWebHandler::handlePost(HttpRequest *request, HttpResponse *response) const
//{

//}

}
