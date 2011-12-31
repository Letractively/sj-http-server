#include "httprequest.h"

HttpRequest::HttpRequest(QTcpSocket * socket)
    :socket(socket), multipart(false), contentLength(0),cachingThreshold(0)
{
    if(socket->canReadLine()) {
        //find the http method
        QString httpMethodLine = QString(socket->readLine());
        setUpMethodAndLocation(httpMethodLine);
    }

    QStringList headers;
    while(socket->canReadLine())
    {
        QString line = QString(socket->readLine());
        if(line.trimmed().length() > 0) {
            headers.push_back(line.trimmed());
        } else {
            //empty line -> end of headers
            break;
        }
    }

    setUpHeaders(headers);
}

void HttpRequest::setUpMethodAndLocation(const QString & methodLine) {
    QStringList list = methodLine.split(' ', QString::SkipEmptyParts);

    if(list.size() < 2) {
        qDebug() << "ERROR - cannot find method and/or location";
        return;
    }

    if("GET" == list[0]) {
        method = GET;
    } else if("POST" == list[0]) {
        method = POST;
    }

    QString locationString = list[1];

    if(locationString.contains('?')) {
        requestUri = locationString.left(locationString.indexOf('?'));
        setUpParameters(locationString);
    } else {
        requestUri = locationString;
    }

}

void HttpRequest::setUpHeaders(const QStringList & headersList)
{
    for(int i = 0; i < headersList.size(); i++) {
        headers.push_back(HttpHeader(headersList[i]));
    }
}

void HttpRequest::setUpParameters(const QString &locationLine)
{
    int pos = locationLine.indexOf('?');
    if(pos < 0) return;

    QString parametersLine = locationLine.right(locationLine.length() - pos - 1);

    QStringList allParametersList = parametersLine.split('&');

    for(int i = 0; i < allParametersList.size(); i++) {
        QStringList singleParameterList = allParametersList[i].split('=');
        if(singleParameterList.size() == 2) {
            parameters.insert(singleParameterList[0], singleParameterList[1]);
        }
    }

}

QString HttpRequest::methodToString()
{
    switch(method) {
    case ERROR: return "ERROR";
    case GET: return "GET";
    case POST: return "POST";
    }
    return "";
}

QString HttpRequest::headersToString()
{
    QString ret = "";
    for(int i = 0; i < headers.size(); i++) {
        ret += headers[i].toString() + "\n";
    }
    return ret;
}

QString HttpRequest::parametersToString()
{
    QString ret = "";

    QList<QString> keys = parameters.keys();

    for(int i = 0; i < keys.size(); i++) {
        ret += keys[i]+"="+parameters[keys[i]]+"\n";
    }

    return ret;
}

QString HttpRequest::toString()
{
    return "HttpRequest: method=["+methodToString()+"]; location=["+requestUri+"]; headers=["
            +headersToString()+"]; parameters=[" + parametersToString()+"]";
}


QString HttpRequest::getHeaderValue(const QString & headerName)
{
    return HttpHeader::getHeaderValue(headerName, headers);
}

quint64 HttpRequest::getContentLength()
{
    if(contentLength == 0) {
        QString contentLengthString = getHeaderValue(HttpHeader::CONTENT_LENGTH);

        if(0 < contentLengthString.length()) {
            bool ok = false;
            int cl = contentLengthString.toInt(&ok);
            if(ok) {
                contentLength = cl;
            }
        }
    }
    return contentLength;
}

void HttpRequest::appendData(const QByteArray & data)
{
    requestData.append(data);
}

QByteArray & HttpRequest::getData()
{
    return requestData;
}


void HttpRequest::addFile(HttpRequestBinaryFile binaryFile)
{
    binaryFiles.push_back(binaryFile);
}

void HttpRequest::addParameter(QString paramName, QString paramValue)
{
    parameters.insert(paramName, paramValue);
}
