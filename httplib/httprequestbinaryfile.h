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
private:
    QByteArray binaryData;
    QString originalFileName;
    QString fileName;
    QDateTime uploadDate;
    QString contentType;
};

#endif // HTTPREQUESTBINARYFILE_H
