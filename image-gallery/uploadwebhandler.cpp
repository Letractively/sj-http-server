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


#include "uploadwebhandler.h"
#include <QDebug>

#include "imagegalleryconstants.h"

namespace SJ {

UploadWebHandler::UploadWebHandler()
{
}

void UploadWebHandler::handle(HttpRequest * request, HttpResponse *response, QSettings::SettingsMap *settings) const
{
    qDebug() << "UploadWebHandler request " << request->getRequestUri();


    switch(request->getMethod()) {
    case HttpRequest::GET:
    {
        QByteArray a = getFormBytes(request->getRequestUri());
        response->writeData(a);
        return;
    }
    case HttpRequest::POST:
    {
        handlePostData(request, response, settings->value(SETTING_TMP_DIR).toString());
        return;
    }

    default:
        break;
    }

    response->setStatusCode(HttpResponse::SC_NOT_FOUND);

}


QByteArray UploadWebHandler::getFormBytes(const QString & requestUri) const
{
    static QString formStringBegin = "<html><body><form action=\"";
    static QString formStringEnd = "\" method=\"POST\" enctype=\"multipart/form-data\">"
            "Image: <INPUT type=\"file\" name=\"imagefile\" /><BR>"
            "<INPUT type=\"submit\" value=\"Upload\" />"
            "</form></body></html>";

    QByteArray a;
    a.append(formStringBegin);
    a.append(requestUri);
    a.append(formStringEnd);

    return a;

}

void UploadWebHandler::handlePostData(HttpRequest *request, HttpResponse *response, const QString &destDir) const
{
    QByteArray a;
    a.append("<html><body>Hello");

    if(request->getBinaryFiles().size() > 0) {
        a.append("<br>thank you for uploading the following files:\n");
        a.append("<ul>");
        for(int i = 0; i < request->getBinaryFiles().size(); i++) {
            HttpRequestBinaryFile binFile = request->getBinaryFiles()[i];
            a.append("<li>" + binFile.getOriginalFileName() + "</li>\n");
            binFile.saveToDisc(destDir);
            a.append("<br>This file is available <a href=\"show?file=" + binFile.getFileName() + "\"> here</a>.");
        }
        a.append("</ul>");
    } else {
        a.append("<br>Unfortunately you haven't uploaded any files...");
    }
    request->getBinaryFiles();

    a.append("</body></html>");
    response->writeData(a);
}

} //namespace SJ
