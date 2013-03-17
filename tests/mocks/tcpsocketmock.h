/*
http://sj-http-server.googlecode.com/

Copyright (C) Jakub Wachowski

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
#include <QDebug>

namespace SJ {

class TcpSocketMock : public QTcpSocket
{

public:
    TcpSocketMock(const QByteArray & data, bool verbose = false);
    virtual bool canReadLine() const;
    virtual qint64 bytesAvailable() const;

protected:
    virtual qint64	readData ( char * data, qint64 maxSize );
    virtual qint64	readLineData ( char * data, qint64 maxlen );
    virtual qint64	writeData ( const char * data, qint64 size );

private:
    QByteArray _data;
    qint64 _readBytes;
    bool _verbose;
};

TcpSocketMock::TcpSocketMock(const QByteArray & data, bool verbose)
    : _data(data), _readBytes(0), _verbose(verbose)
{
}


bool TcpSocketMock::canReadLine() const
{
    if(_verbose) {
        qDebug() << "canReadLine: _readBytes=" << _readBytes << ", _data.size=" << _data.size();
    }

    bool ret = _readBytes < _data.size();

    if(_verbose) {
        qDebug() << "return: " << ret;
    }

    return ret;
}

qint64 TcpSocketMock::readData(char *data, qint64 maxSize)
{
    if(_verbose) {
        qDebug() << "readData: _readBytes=" << _readBytes << ", _data.size=" << _data.size() << ", maxSize=" << maxSize;
    }

    qint64 i;
    for(i = 0;
        (maxSize == 0 || i < maxSize)
        && _readBytes + i < _data.size();
        ++i)
    {
        data[i] = _data.at(_readBytes + i);
    }
    qint64 ret = i;
    _readBytes += ret;

    if(_verbose) {
        qDebug() << "return: " << ret << ", _readBytes=" << _readBytes;
    }

    return ret;
}

qint64 TcpSocketMock::readLineData ( char * data, qint64 maxlen)
{
    if(_verbose) {
        qDebug() << "readLineData: _readBytes=" << _readBytes << ", _data.size=" << _data.size() << ", maxSize=" << maxlen;
    }
    qint64 i;
    for(i = 0;
        (maxlen == 0 || i < maxlen)
        && _readBytes + i < _data.size();
        ++i)
    {
        data[i] = _data.at(_readBytes + i);
        if(data[i] == '\n') {
            i++;
            break;
        }
    }
    qint64 ret = i;
    _readBytes += ret;

    if(_verbose) {
        qDebug() << "return: " << ret << ", _readBytes=" << _readBytes;
    }

    return ret;
}


qint64	TcpSocketMock::writeData ( const char * /* data */, qint64 size )
{
    return size;
}

qint64 TcpSocketMock::bytesAvailable() const
{
    return _data.size() - _readBytes;
}


} //namespace SJ



#endif // TCPSOCKETMOCK_H
