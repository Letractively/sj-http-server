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


#include "httprequestbinaryfile.h"
#include <QFile>
#include <QDebug>

namespace SJ {

HttpRequestBinaryFile::HttpRequestBinaryFile(QByteArray & data, const QString & originalFileName, const QString & contentType)
    : binaryData(data), originalFileName(originalFileName), uploadDate(QDateTime::currentDateTime()), contentType(contentType)
{
    QString fileExtension = originalFileName.mid(originalFileName.indexOf('.'));
    fileName = uploadDate.toString("yyyyMMddhhmmsszzz") + fileExtension;

}

bool HttpRequestBinaryFile::saveToDisc(const QString & destDir) const
{
    QString filePath = destDir + fileName;
    QFile file(filePath);
    file.open(QFile::WriteOnly);
    file.write(this->binaryData);
    file.flush();
    file.close();

    qDebug() << "file saved to " << filePath;
    return true;
}

} // namespace SJ
