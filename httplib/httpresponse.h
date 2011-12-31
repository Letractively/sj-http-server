#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QString>
#include <QVector>
#include <QByteArray>
#include <QTcpSocket>
#include <QFile>

#include "httpheader.h"

class HttpResponse
{
public:

    enum StatusCode {OK = 200, NOT_FOUND = 404};

    HttpResponse();
    HttpResponse(StatusCode code);
    HttpResponse(QByteArray * data, QString contentType = "text/html");
    HttpResponse(QString filePath, QString contentType = "");
    ~HttpResponse();

    void setStatusCode(StatusCode code);
    void addHeader(QString name, QString value);
    void writeToSocket(QTcpSocket * socket);

private:
    static const char * EOL;
    static QString codeToString(StatusCode code);
    static QString guessContentType(QString filePath);
    void setDefaultHeaders();

    StatusCode code;
    QVector<HttpHeader> headers;
    QByteArray data;
    QFile * file;
};

#endif // HTTPRESPONSE_H
