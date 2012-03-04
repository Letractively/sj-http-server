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


#ifndef HTTPREQUESTBINARYFILE_H
#define HTTPREQUESTBINARYFILE_H

#include <QString>
#include <QDateTime>
#include <QByteArray>


class HttpRequestBinaryFile
{
public:
    HttpRequestBinaryFile() {}
    HttpRequestBinaryFile(QByteArray & data, const QString & originalFileName, const QString & contentType);
    QByteArray getData() const { return binaryData; }
    QString getOriginalFileName() const { return originalFileName; }
    QString getFileName() const { return fileName; }
    QString getContentType() const { return contentType; }
    QDateTime getUploadDate() const {return uploadDate; }
    bool saveToDisc(const QString & destDir) const;
private:
    QByteArray binaryData;
    QString originalFileName;
    QString fileName;
    QDateTime uploadDate;
    QString contentType;
};

#endif // HTTPREQUESTBINARYFILE_H
