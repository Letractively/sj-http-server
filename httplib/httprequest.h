#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QByteArray>
#include <QTcpSocket>
#include <QStringList>
#include <QVector>
#include <QMap>

#include "httpheader.h"
#include "httprequestbinaryfile.h"

class HttpRequest
{
//piblic types
public:
    enum RequestMethod {ERROR, GET, POST};

//public member functions
public:
    HttpRequest(QTcpSocket * socket);
    QString getRequestUri() {return requestUri;}
    RequestMethod getMethod() {return method;}
    bool isMultipart() {return multipart; }
    QString toString();

    QString getHeaderValue(const QString & headerName);

    QVector<HttpHeader> getHeaders() {return headers;}

    quint64 getContentLength();

    void appendData(const QByteArray & data);
    QByteArray & getData();

    void addFile(HttpRequestBinaryFile binaryFile);
    void addParameter(QString paramName, QString paramValue);

//private member functions
private:
    void setUpMethodAndLocation(const QString & methodLine);
    void setUpHeaders(const QStringList & tokensList);
    void setUpParameters(const QString & locationLine);
    QString methodToString();
    QString headersToString();
    QString parametersToString();

    void parseData(QByteArray & data);
    void parsePart(const QByteArray & part);


//private fields
private:
    RequestMethod method;
    QString requestUri;
    QVector<HttpHeader> headers;
    QTcpSocket * socket;
    QMap<QString, QString> parameters;
    QVector<HttpRequestBinaryFile> binaryFiles;
    bool multipart;
    quint64 contentLength;
    quint64 cachingThreshold;
    QByteArray requestData;

};

#endif // HTTPREQUEST_H
