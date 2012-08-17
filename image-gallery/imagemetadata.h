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

#ifndef IMAGEMETADATA_H
#define IMAGEMETADATA_H

#include <QString>
#include <QDateTime>
#include "httprequestbinaryfile.h"

namespace SJ {

class ImageMetadata
{
public:
    ImageMetadata();
    ImageMetadata(const QString & title, const QString & author, const QString & filename, const QDateTime & uploadDate, const QString & originalFilename);

    QString getTitle() const { return title; }
    QString getAuthor() const {return author; }
    QString getFilename() const {return filename;}
    QString getOriginalFilename() const { return originalFilename; }
    QDateTime getUploadDate() const { return uploadDate; }

    QString toString() const;
private:
    QString title;
    QString author;
    QString filename;
    QDateTime uploadDate;
    QString originalFilename;

};

} //namespace SJ

#endif // IMAGEMETADATA_H
