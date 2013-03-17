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


#ifndef IMAGEMETADATAXMLPROVIDER_H
#define IMAGEMETADATAXMLPROVIDER_H

#include "imagemetadataprovider.h"
#include "imagemetadatamemoryprovider.h"
#include "loggerall.h"
#include <QMutex>
#include <QMutexLocker>

namespace SJ {

class ImageMetadataXmlProvider : public ImageMetadataProvider
{
public:
    ImageMetadataXmlProvider(const QString & xmlFile);
    virtual ~ImageMetadataXmlProvider();

    virtual void addImage(const ImageMetadata & image);
    virtual QList<ImageMetadata> getImages();
    virtual void flush();

private:
    ImageMetadataMemoryProvider * memoryProvider;
    QString xmlFile;
    void init();
    bool needSync;
    const static QString NS;
    QMutex fileAccessMutex;
};

} // namespace SJ

#endif // IMAGEMETADATAXMLPROVIDER_H
