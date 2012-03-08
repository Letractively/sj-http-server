/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include "imagegallery.h"
#include "contextpathdispatcher.h"
#include "QDebug"
#include "mainpagewebhandler.h"
#include "uploadwebhandler.h"
#include "imagegalleryconstants.h"

ImageGallery::ImageGallery()
{
    QList<ContextPathPair> handlersList;
    handlersList.append(ContextPathPair("/upload", new UploadWebHandler(), true));
    handlersList.append(ContextPathPair("/*", new MainPageWebHandler(), true));
    dispatcher = new ContextPathDispatcher(handlersList);
}

ImageGallery::~ImageGallery()
{
    if(dispatcher != 0) {
        delete dispatcher;
        dispatcher = 0;
    }
}

QString ImageGallery::name() const
{
    return "ImageGallery";
}

HttpResponse ImageGallery::handle(HttpRequest *req, QSettings::SettingsMap *settings) const
{
//    qDebug() << "IMAGE-GALLERY REQUEST"  << req->toString();



    return dispatcher->dispatchRequest(req)->handle(req, settings);
}



QVector<SettingsItem> ImageGallery::supportedSettings() const
{
    QVector<SettingsItem> vect;
    vect.push_back(SettingsItem("Temp Directory", SettingsItem::DIRECTORY, SETTING_TMP_DIR));
    return vect;
}






Q_EXPORT_PLUGIN2(image-gallery, ImageGallery)
