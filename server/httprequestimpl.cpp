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


#include "httprequestimpl.h"
#include "serverutils.h"

#include <QUuid>
namespace SJ {

const Logger & HttpRequestImpl::logger = LoggerFactory::instance().getLogger("sj-server-logger");

HttpRequestImpl::HttpRequestImpl(QTcpSocket * socket)
    : contentLength(0),
      requestUri(""),
      requestUrl(""),
      cachingThreshold(0),
      requestId(QUuid::createUuid().toString())
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

HttpRequestImpl::HttpRequestImpl()
{
    requestId = QUuid::createUuid().toString();
}

QString HttpRequestImpl::getRequestUri() const
{
    if(requestUri == "") {
        // not yet parsed
        if(location.startsWith("/")) {
            requestUri = location;
        } else {
            int protocolPos = location.indexOf("://");
            if(protocolPos < 0) {
                protocolPos = 0;
            }
            requestUri = Utils::substring(location, location.indexOf("/", protocolPos));
        }
    }
    return requestUri;
}

QString HttpRequestImpl::getRequestUrl() const
{
    if(requestUrl == "") {
        //not yet parsed
        if(location.startsWith("http://")) {
            requestUrl = location;
        } else {
            requestUrl = "http://" + getHeaderValue("Host") + getRequestUri();
        }
    }
    return requestUrl;
}

HttpRequest::RequestMethod HttpRequestImpl::getMethod() const
{
    return method;
}

QString HttpRequestImpl::getParameter(const QString & paramName) const
{
    return parameters.value(paramName);
}

QString HttpRequestImpl::getHeaderValue(const QString & headerName) const
{
    return HttpHeader::getHeaderValue(headerName, headers);
}

QVector<HttpHeader> HttpRequestImpl::getHeaders() const
{
    return headers;
}

QVector<HttpRequestBinaryFile> HttpRequestImpl::getBinaryFiles() const
{
    return binaryFiles;
}


void HttpRequestImpl::setUpMethodAndLocation(const QString & methodLine)
{
    QStringList list = methodLine.split(' ', QString::SkipEmptyParts);

    if(list.size() < 2) {
        LOG_WARN(logger, "ERROR - cannot find method and/or location");
        return;
    }

    if("GET" == list[0]) {
        method = GET;
    } else if("POST" == list[0]) {
        method = POST;
    } else if("PUT" == list[0]) {
        method = PUT;
    } else if("DELETE" == list[0]) {
        method = DELETE;
    }

    QString locationString = list[1];

    if(locationString.contains('?')) {
        location = locationString.left(locationString.indexOf('?'));
        setUpParameters(locationString);
    } else {
        location = locationString;
    }

}

void HttpRequestImpl::setUpHeaders(const QStringList & headersList)
{
    for(int i = 0; i < headersList.size(); i++) {
        headers.push_back(HttpHeader(headersList[i]));
    }
}

void HttpRequestImpl::setUpParameters(const QString &locationLine)
{
    int pos = locationLine.indexOf('?');
    if(pos < 0) return;

    QString parametersLine = locationLine.right(locationLine.length() - pos - 1);

    QStringList allParametersList = parametersLine.split('&');

    for(int i = 0; i < allParametersList.size(); i++) {
        QStringList singleParameterList = allParametersList[i].split('=');
        if(singleParameterList.size() == 2) {
            parameters.insert(singleParameterList[0], singleParameterList[1]);
        } else if(singleParameterList.size() == 1) {
            parameters.insert(singleParameterList[0], "");
        }
    }

}

QString HttpRequestImpl::methodToString()
{
    switch(method) {
    case GET: return "GET";
    case POST: return "POST";
    case OPTIONS: return "OPTIONS";
    case HEAD: return "HEAD";
    case CONNECT: return "CONNECT";
    case PUT: return "PUT";
    case DELETE: return "DELETE";
    case TRACE: return "TRACE";
    }
    return "";
}

QString HttpRequestImpl::headersToString()
{
    QString ret = "";
    for(int i = 0; i < headers.size(); i++) {
        ret += headers[i].toString() + "\n";
    }
    return ret;
}

QString HttpRequestImpl::parametersToString()
{
    QString ret = "";

    QList<QString> keys = parameters.keys();

    for(int i = 0; i < keys.size(); i++) {
        ret += keys[i]+"="+parameters[keys[i]]+"; ";
    }
    return ret;
}

QString HttpRequestImpl::toString()
{
    QString s("");

    s += "HttpRequest:\n";
    s += "method      [" + methodToString() + "];\n";
    s += "requestUri  [" + getRequestUri() + "];\n";
    s += "requestUrl  [" + getRequestUrl()+ "];\n";
    s += "parameters  [" + parametersToString() + "];\n";
    s += "headers     [" + headersToString() +"];\n";
    return s;
}




quint64 HttpRequestImpl::getContentLength()
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

void HttpRequestImpl::appendData(const QByteArray & data)
{
    requestData.append(data);
}

QByteArray & HttpRequestImpl::getData()
{
    return requestData;
}


void HttpRequestImpl::addFile(HttpRequestBinaryFile binaryFile)
{
    binaryFiles.push_back(binaryFile);
    LOG_DEBUG(logger, LogBuilder("Adding file ").append(binaryFile.getOriginalFileName()).append(", so now there are ").append(binaryFiles.size()).append(" files"));
}

void HttpRequestImpl::addParameter(QString paramName, QString paramValue)
{
    parameters.insert(paramName, paramValue);
}
QString HttpRequestImpl::getRequestID() const
{
    return requestId;
}

} // namespace SJ
