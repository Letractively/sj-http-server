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


#include "uploadwebhandler.h"
#include <QDebug>

UploadWebHandler::UploadWebHandler()
{
}

HttpResponse UploadWebHandler::handle(HttpRequest * request, QSettings::SettingsMap *settings) const
{
    qDebug() << "UploadWebHandler request " << request->getRequestUri();


    switch(request->getMethod()) {
    case HttpRequest::GET:
    {
        QByteArray a = getFormBytes(request->getRequestUri());
        return HttpResponse(&a);
    }
    case HttpRequest::POST:
    {
        return handlePostData(request, settings->value("temp.directory").toString());
    }

    default:
        break;
    }

    return HttpResponse(HttpResponse::NOT_FOUND);

}


QByteArray UploadWebHandler::getFormBytes(const QString & requestUri) const
{
    static QString formStringBegin = "<html><body><form action=\"";
    static QString formStringEnd = "\" method=\"POST\" enctype=\"multipart/form-data\">"
            "First name: <INPUT type=\"text\" name=\"firstname\" /><BR>"
            "Image: <INPUT type=\"file\" name=\"imagefile\" /><BR>"
            "<INPUT type=\"submit\" value=\"Upload\" />"
            "</form></body></html>";

    QByteArray a;
    a.append(formStringBegin);
    a.append(requestUri);
    a.append(formStringEnd);

    return a;

}

HttpResponse UploadWebHandler::handlePostData(HttpRequest *request, const QString & destDir) const
{
    QByteArray a;
    a.append("<html><body>Hello " + request->getParameter("firstname"));

    if(request->getBinaryFiles().size() > 0) {
        a.append("<br>thank you for uploading the following files:\n");
        a.append("<ul>");
        for(int i = 0; i < request->getBinaryFiles().size(); i++) {
            a.append("<li>" + request->getBinaryFiles()[i].getOriginalFileName() + "</li>\n");
            request->getBinaryFiles()[i].saveToDisc(destDir);
        }
        a.append("</ul>");
    }
    request->getBinaryFiles();

    a.append("</body></html>");
    return HttpResponse(&a);
}
