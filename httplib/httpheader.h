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


#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <QString>
#include <QVector>

namespace SJ {

/**
 * @brief Represents an http header as specified in RFC 2616 section 4.2
 */
class HttpHeader
{
public:
    // set of known http headers
    static const QString CONTENT_TYPE;
    static const QString ACCEPT_CHARSET;
    static const QString CONTENT_DISPOSITION;
    static const QString CONTENT_LENGTH;


    /**
     * @brief Searches for a header in a vector of headers and returns its value
     *
     * If vector of headers contains more than one header with a given name, then a first one is returned.
     * If vector does not contain such a header, an empty string is returned
     *
     * @param headerName name of the header
     * @param headers vector of headers
     * @return header value or empty string if header not found
     */
    static QString getHeaderValue(const QString & headerName, const QVector<HttpHeader> & headers);



    /**
     * @brief Searches for a header in a vector of headers and returns its values
     *
     * If vector of headers contains more than one header with a given name, then all velues are returnd.
     * If vector does not contain such a header, an empty vector is returned
     *
     * @param headerName name of the header
     * @param headers vector of headers
     * @return header vector of values or empty vector if header not found
     */
    static QVector<QString> getHeaderValues(const QString & headerName, const QVector<HttpHeader> & headers);


    /**
     * @brief Creates an empty http header
     */
    HttpHeader();

    /**
     * @brief Creates an http header with given name and value
     * @param name name of the header
     * @param value header value
     */
    HttpHeader(const QString & name, const QString & value);

    /**
     * @brief Parses a line of HTTP header and creates a header object
     *
     * Line to be parsed should be like in the http protocol, for example
     * @verbatim
     * Content-Type: text/html
     * @endverbatim
     * produces a header with name 'Content-Type' and value 'text/html'
     *
     * @param line http protocol line to be parsed
     */
    HttpHeader(const QString & line);

    /**
     * @brief returns a header ain the form 'name: value"
     * @return http header line
     */
    QString toString();

    /**
     * Returns name of the header
     * @return name of the header
     */
    QString getName() const { return name; }

    /**
     * Returns value of the header
     * @return value of the header
     */
    QString getValue() const {return value; }

private:
    QString name;
    QString value;
};

} //namespace SJ

#endif // HTTPHEADER_H
