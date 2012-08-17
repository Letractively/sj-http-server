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

#include "imagemetadata.h"

namespace SJ {

ImageMetadata::ImageMetadata()
{
}

ImageMetadata::ImageMetadata(const QString & title, const QString & author,
                             const QString & filename, const QDateTime & uploadDate,
                             const QString & originalFilename)
    : title(title),
      author(author),
      filename(filename),
      uploadDate(uploadDate),
      originalFilename(originalFilename)
{
}

QString ImageMetadata::toString() const
{
    return "title=[" + title + "] author=[" + author + "], filename=[" + filename + "], uploadDate=[" + uploadDate.toString("yyyy-MM-dd hh:mm:ss") + "]";
}

}
