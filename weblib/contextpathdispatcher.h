/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Jakub Wachowski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef CONTEXTPATHDISPATCHER_H
#define CONTEXTPATHDISPATCHER_H

#include "abstractdispatcher.h"
#include "errorwebhandler.h"

class ContextPathPair;

class ContextPathDispatcher : public AbstractDispatcher
{
public:
    ContextPathDispatcher(QList<ContextPathPair> paths);
    ~ContextPathDispatcher();
    AbstractWebHandler * dispatchRequest(HttpRequest * request) const;
private:
    QList<ContextPathPair> paths;
    ErrorWebHandler * errorWebHandler;

};



class ContextPathPair
{
public:
    ContextPathPair(const QString & path, AbstractWebHandler * handler, bool deleteByDispatcher = true)
        :path(path), handler(handler), deleteByDispatcher(deleteByDispatcher)
    {}

    QString getPath() const {
        return path;
    }

    AbstractWebHandler * getHandler() const {
        return handler;
    }

private:
    QString path;
    AbstractWebHandler * handler;
    bool deleteByDispatcher;

    friend class ContextPathDispatcher;
};

#endif // CONTEXTPATHDISPATCHER_H
