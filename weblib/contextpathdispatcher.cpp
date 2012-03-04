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


#include "contextpathdispatcher.h"
#include <QRegExp>

ContextPathDispatcher::ContextPathDispatcher(QList<ContextPathPair> paths)
    : paths(paths)
{
    errorWebHandler = new ErrorWebHandler();
}

ContextPathDispatcher::~ContextPathDispatcher()
{
    if(errorWebHandler != 0) {
        delete errorWebHandler;
        errorWebHandler = 0;
    }

    for(int i = 0; i < paths.length(); ++i) {
        if(paths[i].deleteByDispatcher) {
            delete paths[i].getHandler();
        }
    }
}


AbstractWebHandler * ContextPathDispatcher::dispatchRequest(HttpRequest * request) const
{

    for(int i = 0; i < paths.size(); ++i) {
        QRegExp regExp(paths[i].getPath(), Qt::CaseInsensitive, QRegExp::Wildcard);

        if(regExp.exactMatch(request->getRelativePath())) {
            qDebug() << "ContextPathDispatcher: " << request->getRelativePath() << " matches " << regExp.pattern();
            return paths[i].getHandler();
        } else {
            qDebug() << "ContextPathDispatcher: " << request->getRelativePath() << " does not match " << regExp.pattern();
        }
    }

    return errorWebHandler;
}
