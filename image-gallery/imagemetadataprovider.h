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

#ifndef IMAGEMETADATAPROVIDER_H
#define IMAGEMETADATAPROVIDER_H

#include <QString>
#include <QList>
#include "imagemetadata.h"

namespace SJ {

class ImageMetadataProvider
{
public:

    static ImageMetadataProvider * getInstance();

    virtual ~ImageMetadataProvider();

    virtual void addImage(const ImageMetadata & image) = 0;
    virtual QList<ImageMetadata> getImages() = 0;

    virtual void flush();

protected:
    ImageMetadataProvider();
    static const Logger & logger;

private:
    static ImageMetadataProvider * provider;
};

} //namespace SJ

#endif // IMAGEMETADATAPROVIDER_H
