#include "httprequestbinaryfile.h"

HttpRequestBinaryFile::HttpRequestBinaryFile(QByteArray & data, const QString & originalFileName, const QString & contentType)
    : binaryData(data), originalFileName(originalFileName), uploadDate(QDateTime::currentDateTime()), contentType(contentType)
{
    QString fileExtension = originalFileName.mid(originalFileName.indexOf('.'));
    fileName = uploadDate.toString("yyyyMMddhhmmsszzz") + fileExtension;

}
