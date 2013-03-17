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


#include "httprequestbinaryfile.h"
#include <QFile>

namespace SJ {

HttpRequestBinaryFile::HttpRequestBinaryFile(QByteArray & data, const QString & originalFileName, const QString & contentType)
    : binaryData(data), originalFileName(originalFileName), uploadDate(QDateTime::currentDateTime()), contentType(contentType)
{
}


QString HttpRequestBinaryFile::getFileExtension() const
{
    int posOfLastDot = originalFileName.lastIndexOf('.');
    if(posOfLastDot <= 0) {
        return "";
    }
    return originalFileName.mid(posOfLastDot);
}

} // namespace SJ
