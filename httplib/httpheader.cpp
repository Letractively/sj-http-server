#include "httpheader.h"

const QString HttpHeader::CONTENT_TYPE = "Content-Type";
const QString HttpHeader::ACCEPT_CHARSET = "Accept-Charset";
const QString HttpHeader::CONTENT_DISPOSITION = "Content-Disposition";
const QString HttpHeader::CONTENT_LENGTH = "Content-Length";

HttpHeader::HttpHeader()
    : name(""), value("")
{

}

QString HttpHeader::getHeaderValue(const QString & headerName, const QVector<HttpHeader> & headers)
{
    for(int i = 0; i < headers.size(); i++) {
        if(headers[i].getName() == headerName)
        {
            return headers[i].getValue();
        }
    }
    return "";
}

HttpHeader::HttpHeader(const QString & name, const QString & value)
    : name(name), value(value)
{
}

HttpHeader::HttpHeader(const QString & line)
{
    name = line.left(line.indexOf(':'));
    value = line.right(line.length() - line.indexOf(':') - 1).trimmed();
}




QString HttpHeader::toString() {
    return name + ": " + value;
}


