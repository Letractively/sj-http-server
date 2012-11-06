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


#ifndef HTTPREQUESTBINARYFILE_H
#define HTTPREQUESTBINARYFILE_H

#include <QString>
#include <QDateTime>
#include <QByteArray>
#include "loggerall.h"

namespace SJ {

/**
 * @brief Class representing a binary file that is sent within a request
 */
class HttpRequestBinaryFile
{
public:
    /**
     * @brief Empty Constructor
     */
    HttpRequestBinaryFile() {}
    /**
     * @brief Constructor
     * @param data binary data of the file
     * @param originalFileName the original name of the uploaded file
     * @param contentType the type of the file
     */
    HttpRequestBinaryFile(QByteArray & data, const QString & originalFileName = "", const QString & contentType = "");
    QByteArray getData() const { return binaryData; }
    QString getOriginalFileName() const { return originalFileName; }
    QString getContentType() const { return contentType; }
    QDateTime getUploadDate() const {return uploadDate; }
    QString getFileExtension() const;
private:
    QByteArray binaryData;
    QString originalFileName;
    QDateTime uploadDate;
    QString contentType;
};

} //namespace SJ

#endif // HTTPREQUESTBINARYFILE_H
