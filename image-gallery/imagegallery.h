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


#ifndef IMAGEGALLERY_H
#define IMAGEGALLERY_H

#include <abstractrequesthandler.h>
#include <abstractdispatcher.h>
#include <QObject>

namespace SJ {

class ImageGallery : public QObject, public AbstractRequestHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "sj-http-server.image-gallery" FILE "image-gallery.json")
    Q_INTERFACES(SJ::AbstractRequestHandler)
public:
    ImageGallery();
    ~ImageGallery();
    void init(const QMap<QString, QVariant> & initParams);
    void handleGet(HttpRequest *req, HttpResponse * resp) const;
    void handlePost(HttpRequest *req, HttpResponse * resp) const;
    QString name() const;
private:
    AbstractDispatcher * dispatcher;
};

} //namespace SJ

#endif // IMAGEGALLERY_H
