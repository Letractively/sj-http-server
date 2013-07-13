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


#include "imagegallery.h"
#include "contextpathdispatcher.h"
#include "mainpagewebhandler.h"
#include "uploadwebhandler.h"
#include "imageviewwebhandler.h"
#include "imagegalleryconstants.h"
#include "imagemetadataprovider.h"
#include <QDebug>

namespace SJ {

ImageGallery::ImageGallery()
{
    QList<ContextPathPair> handlersList;
    handlersList.append(ContextPathPair("/upload", new UploadWebHandler(), true));
    handlersList.append(ContextPathPair("/show", new ImageViewWebHandler(), true));
    handlersList.append(ContextPathPair("/*", new MainPageWebHandler(), true));
    dispatcher = new ContextPathDispatcher(handlersList);
}

ImageGallery::~ImageGallery()
{
    if(dispatcher != 0) {
        delete dispatcher;
        dispatcher = 0;
    }

    ImageMetadataProvider::getInstance()->flush();
}

void ImageGallery::init(const QMap<QString, QVariant> &  initParams)
{
    qDebug() << initParams;
}

void ImageGallery::handle(HttpRequest * req, HttpResponse * response) const
{
    dispatcher->dispatchRequest(req)->handle(req, response);
}

QString ImageGallery::name() const
{
    return "ImageGallery";
}



} // namespace SJ

