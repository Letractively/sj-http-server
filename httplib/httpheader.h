#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <QString>
#include <QVector>

class HttpHeader
{
public:
    static const QString CONTENT_TYPE;
    static const QString ACCEPT_CHARSET;
    static const QString CONTENT_DISPOSITION;
    static const QString CONTENT_LENGTH;


    static QString getHeaderValue(const QString & headerName, const QVector<HttpHeader> & headers);

    HttpHeader();
    HttpHeader(const QString & name, const QString & value);
    HttpHeader(const QString & line);
    QString toString();

    QString getName() const { return name; }
    QString getValue() const {return value; }

private:
    QString name;
    QString value;
};

#endif // HTTPHEADER_H
