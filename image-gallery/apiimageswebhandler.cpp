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
#include <QJsonParseError>
#include <QFile>
#include <QDateTime>

namespace SJ {

ApiImagesWebHandler::ApiImagesWebHandler(const QString & context, const QString &imagesDir)
    : contextRoot(context), imagesDir(imagesDir)
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

void ApiImagesWebHandler::handlePost(HttpRequest *request, HttpResponse *response) const
{
    const QByteArray& data = request->getContent();
    QJsonParseError error;
    QJsonDocument jd = QJsonDocument::fromJson(data, &error);

    if(error.error != QJsonParseError::NoError) {
        response->setStatusCode(HttpResponse::StatusCode::SC_BAD_REQUEST);
        response->writeData(error.errorString());
        return;
    }

    QJsonObject jo = jd.object();
    QString author = jo["author"].toString();
    QString title = jo["title"].toString();
    QString origFilename = jo["originalFileName"].toString();
    QByteArray imageData;
    imageData.append(jo["data"].toString());
    imageData = QByteArray::fromBase64(imageData);

    QStringList of = origFilename.split(".");
    QString fileExt = of.last();
    QString filename = saveToDisc(imageData, imagesDir, "." + fileExt);
    ImageMetadata meta(title, author, filename, QDateTime::currentDateTime(), origFilename);
    ImageMetadataProvider::getInstance()->addImage(meta);

    response->setStatusCode(HttpResponse::StatusCode::SC_CREATED);
}

QString ApiImagesWebHandler::saveToDisc(const QByteArray & data, const QString & destDir, const QString & fileExtension) const
{
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz") + fileExtension;
    QString filePath = destDir + fileName;
    QFile file(filePath);
    file.open(QFile::WriteOnly);
    file.write(data);
    file.flush();
    file.close();

    return fileName;
}
}
