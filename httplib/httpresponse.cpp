#include "httpresponse.h"

const char * HttpResponse::EOL = "\r\n";


HttpResponse::HttpResponse()
    : code(OK), file(0)
{
    setDefaultHeaders();
}

HttpResponse::HttpResponse(StatusCode code)
    :code(code), file(0)
{
    setDefaultHeaders();
}

HttpResponse::HttpResponse(QByteArray * data, QString contentType)
    : code(OK), data(*data), file(0)
{
    setDefaultHeaders();
    addHeader(HttpHeader::CONTENT_TYPE, contentType);
}

HttpResponse::HttpResponse(QString filePath, QString contentType)
    :code(OK), file(0)
{
    setDefaultHeaders();
    file = new QFile(filePath);
    if(!file->exists()) {
        code = NOT_FOUND;
        delete file;
        return;
    }

    qDebug() << "file size " << file->size();

    if(contentType != "") {
        addHeader(HttpHeader::CONTENT_TYPE, contentType);
    } else {
        //guess content type
        QString type = guessContentType(filePath);
        //add header only if known type - otherwise client will try to guess the type
        if("" != type) {
            addHeader(HttpHeader::CONTENT_TYPE, type);
        }
    }

}

HttpResponse::~HttpResponse()
{
}

void HttpResponse::setStatusCode(StatusCode code)
{
    this->code = code;
}

void HttpResponse::addHeader(QString name, QString value)
{
    headers.push_back(HttpHeader(name, value));
}

void HttpResponse::writeToSocket(QTcpSocket * socket)
{
    socket->write(("HTTP/1.1 " + codeToString(this->code) + EOL).toStdString().c_str());

    if(code == NOT_FOUND) {
        socket->write("ContentType: text/plain");
        socket->write(EOL);
        socket->write("Connection: close");
        socket->write(EOL);
        socket->write(EOL);
        socket->write("Resource not found");
        return;
    }

    qDebug() << "Returning response ";
    qDebug() << "HTTP/1.1 " + codeToString(this->code);

    for(int i = 0; i < headers.size(); ++i) {
        socket->write((headers[i].toString() + EOL).toStdString().c_str());
        qDebug() << headers[i].toString();
    }
    socket->write(EOL);
    qDebug() << "";

    if(data.size() > 0) {
        qDebug() << data;
        socket->write(data);
    }

    if(file != 0 && file->size() > 0) {
        file->open(QFile::ReadOnly);
        const qint64 MAX_SIZE = 256000;

        while(true) {
            QByteArray d = file->read(MAX_SIZE);
            if(d.size() > 0) {
                qDebug() << d;
                socket->write(d);
            } else {
                break;
            }
        }

        file->close();
        delete file;
    }
}

QString HttpResponse::codeToString(StatusCode code)
{
    switch(code) {
    case OK: return "200 OK";
    case NOT_FOUND: return "404 Not Found";
    }
    return "500 Internal Server Error";
}

void HttpResponse::setDefaultHeaders()
{
    addHeader("Connection", "close");
    addHeader("Server", "JWServer v. 0.1");
}


QString HttpResponse::guessContentType(QString filePath)
{
    QString filePathLower = filePath.toLower();

    if(filePathLower.endsWith(".html") || filePathLower.endsWith(".htm")) {
        return "text/html";
    }

    if(filePathLower.endsWith(".txt")) {
        return "image/plain";
    }

    if(filePathLower.endsWith(".png")) {
        return "image/png";
    }

    if(filePathLower.endsWith(".jpg") || filePathLower.endsWith(".jpeg")) {
        return "image/jpeg";
    }

    if(filePathLower.endsWith(".gif")) {
        return "image/gif";
    }

    if(filePathLower.endsWith(".tiff")) {
        return "image/tiff";
    }

    if(filePathLower.endsWith(".pdf")) {
        return "application/pdf";
    }

    if(filePathLower.endsWith(".mp4")) {
        return "video/mp4";
    }


    if(filePathLower.endsWith(".ico")) {
        return "image/x-icon";
    }

    return "";
}


