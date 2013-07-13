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


#include "contextpathdispatcher.h"
#include "loggerall.h"
#include <QRegExp>

namespace SJ {

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
    const Logger & logger = LoggerFactory::instance().getLogger("weblib-logger");

    QString requestedUri = request->getRequestUri();
    requestedUri = requestedUri.right(requestedUri.length() - requestedUri.indexOf("/", 1));

    for(int i = 0; i < paths.size(); ++i) {
        QRegExp regExp(paths[i].getPath(), Qt::CaseInsensitive, QRegExp::Wildcard);

        if(regExp.exactMatch(requestedUri)
                || (!requestedUri.endsWith("/") && regExp.exactMatch(requestedUri + "/"))) {
            LOG_DEBUG(logger, LogBuilder("ContextPathDispatcher: ").append(request->getRequestUri())
                      .append(" matches ").append(regExp.pattern()).toString());
            return paths[i].getHandler();
        } else {
            LOG_TRACE(logger, LogBuilder("ContextPathDispatcher: ").append(request->getRequestUri())
                      .append(" does not match ").append(regExp.pattern()).toString());
        }
    }

    return errorWebHandler;
}

} //namespace SJ
