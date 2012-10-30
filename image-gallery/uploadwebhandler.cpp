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
#include "imagemetadata.h"
#include "imagemetadataprovider.h"

namespace SJ {

const Logger & UploadWebHandler::logger = LoggerFactory::instance().getLogger(LOGGER_NAME);

UploadWebHandler::UploadWebHandler()
{
}

void UploadWebHandler::handle(HttpRequest * request, HttpResponse *response, QSettings::SettingsMap *settings) const
{
    LOG_TRACE(logger, "UploadWebHandler handle called");


    switch(request->getMethod()) {
    case HttpRequest::GET:
    {
        LOG_TRACE(logger, "GET method - returning upload form");
        QByteArray a = getFormBytes(request->getRequestUri());
        response->writeData(a);
        return;
    }
    case HttpRequest::POST:
    {
        LOG_TRACE(logger, "POST method - reading posted data");
        handlePostData(request, response, settings->value(SETTING_TMP_DIR).toString());
        return;
    }

    default:
        LOG_WARN(logger, LogBuilder("Unsupported method [")
                 .append(request->getMethod()).append("] called, ignoring").toString());
        response->setStatusCode(HttpResponse::SC_BAD_REQUEST);
        break;
    }
}


QByteArray UploadWebHandler::getFormBytes(const QString & requestUri) const
{
    static QString formStringBegin = "<html><body><form action=\"";
    static QString formStringEnd = "\" method=\"POST\" enctype=\"multipart/form-data\">"
            "Author: <INPUT type=\"text\" name=\"author\" /><BR>"
            "Title: <INPUT type=\"text\" name=\"title\" /><BR>"
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
            a.append("<br>This file is available <a href=\"show?file=" + binFile.getFileName() + "\">here</a>.");

            ImageMetadata img(
                        request->getParameter("title"),
                        request->getParameter("author"),
                        binFile.getFileName(),
                        binFile.getUploadDate(),
                        binFile.getOriginalFileName()
                        );


          ImageMetadataProvider::getInstance()->addImage(img);

        }
        a.append("</ul>");
    } else {
        a.append("<br>Unfortunately you haven't uploaded any files...");
    }

    a.append("</body></html>");
    response->writeData(a);
}

} //namespace SJ
