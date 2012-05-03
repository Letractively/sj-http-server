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


#ifndef TCPSOCKETMOCK_H
#define TCPSOCKETMOCK_H

#include <QTcpSocket>
#include <QByteArray>

namespace SJSERVER {

class TcpSocketMock : public QTcpSocket
{

public:
    TcpSocketMock(const QByteArray & data);
    virtual bool canReadLine() const;

protected:
    virtual qint64	readData ( char * data, qint64 maxSize );
    virtual qint64	readLineData ( char * data, qint64 maxlen );
    virtual qint64	writeData ( const char * data, qint64 size );

private:
    QByteArray _data;
    qint64 _readBytes;


};

TcpSocketMock::TcpSocketMock(const QByteArray & data)
    : _data(data), _readBytes(0)
{
}


bool TcpSocketMock::canReadLine() const
{
    return _readBytes < _data.size();
}

qint64 TcpSocketMock::readData(char *data, qint64 maxSize)
{
    qint64 i;
    for(i = 0;
        (maxSize == 0 || i < maxSize)
        && _readBytes + i < _data.size();
        ++i)
    {
        data[i] = _data.at(_readBytes + i);
    }
    _readBytes += i +1;
    return i + 1;
}

qint64 TcpSocketMock::readLineData ( char * data, qint64 maxlen)
{
    qint64 i;
    for(i = 0;
        (maxlen == 0 || i < maxlen)
        && _readBytes + i < _data.size();
        ++i)
    {
        data[i] = _data.at(_readBytes + i);
        if(_data.at(_readBytes + i) == '\n') {
            break;
        }
    }
    _readBytes += i + 1;
    return i + 1;
}


qint64	TcpSocketMock::writeData ( const char * /* data */, qint64 size )
{
    return size;
}

} //namespace SJSERVER



#endif // TCPSOCKETMOCK_H
