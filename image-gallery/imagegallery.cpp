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
#include "apiimageswebhandler.h"
#include <QDebug>

namespace SJ {

ImageGallery::ImageGallery()
{

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
    QString imagesDir = initParams.value(ImgGal::SETTING_TMP_DIR).toString();
    QString contextRoot = initParams.value(AbstractRequestHandler::CONTEXT_ROOT_INIT_PARAM).toString();

    QList<ContextPathPair> handlersList;
    handlersList.append(ContextPathPair("/upload", new UploadWebHandler(imagesDir), true));
    handlersList.append(ContextPathPair("/show", new ImageViewWebHandler(imagesDir), true));
    handlersList.append(ContextPathPair("/api/images", new ApiImagesWebHandler(contextRoot, imagesDir), true));
    handlersList.append(ContextPathPair("/*", new MainPageWebHandler(), true));
    dispatcher = new ContextPathDispatcher(handlersList);
}

void ImageGallery::handleGet(HttpRequest * req, HttpResponse * response) const
{
    dispatcher->dispatchRequest(req)->handleGet(req, response);
}

void ImageGallery::handlePost(HttpRequest * req, HttpResponse * response) const
{
    dispatcher->dispatchRequest(req)->handlePost(req, response);
}

QString ImageGallery::name() const
{
    return "ImageGallery";
}



} // namespace SJ

