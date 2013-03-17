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


#include "imagemetadataxmlprovider.h"
#include "QXmlStreamWriter"
#include "QXmlStreamReader"
#include "QFile"

namespace SJ {

const QString ImageMetadataXmlProvider::NS = "http://sj-http-server.googlecode.com/image-gallery";

ImageMetadataXmlProvider::ImageMetadataXmlProvider(const QString & xmlFile)
    : memoryProvider(0), xmlFile(xmlFile), needSync(false)
{
}

ImageMetadataXmlProvider::~ImageMetadataXmlProvider() {
    flush();
    delete memoryProvider;
}

void ImageMetadataXmlProvider::flush()
{
    if(needSync) {
        QMutexLocker locker(&fileAccessMutex);
        LOG_INFO(logger, "syncing images data with xml file");

        QFile file(xmlFile);
        file.open(QFile::WriteOnly | QFile::Text);


        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.setAutoFormattingIndent(2);

        writer.writeStartDocument();
        writer.writeNamespace(NS, "sj");
        writer.writeStartElement(NS, "images");

        for(int i = 0; i < memoryProvider->getImages().size(); ++i) {
            ImageMetadata img = memoryProvider->getImages().at(i);
            writer.writeEmptyElement(NS, "image");
            writer.writeAttribute("title", img.getTitle());
            writer.writeAttribute("author", img.getAuthor());
            writer.writeAttribute("filename", img.getFilename());
            writer.writeAttribute("uploadDate", img.getUploadDate().toString(Qt::ISODate));
            writer.writeAttribute("originalFilename", img.getOriginalFilename());
        }


        writer.writeEndElement();
        writer.writeEndDocument();

        file.close();
        needSync = false;
    }
}

void ImageMetadataXmlProvider::addImage(const ImageMetadata & image)
{
    init();
    needSync = true;
    memoryProvider->addImage(image);
}

QList<ImageMetadata> ImageMetadataXmlProvider::getImages()
{
    init();
    return memoryProvider->getImages();
}

void ImageMetadataXmlProvider::init()
{
    if(memoryProvider != 0) {
        //already initialized
        return;
    }

    memoryProvider = new ImageMetadataMemoryProvider();
    QFile file(xmlFile);
    if(file.exists())
    {
        QMutexLocker locker(&fileAccessMutex);

        LOG_DEBUG(logger, "Starting image xml provider initialization...");



        file.open(QFile::ReadOnly | QFile::Text);

        LOG_INFO(logger, LogBuilder().append(file.exists()));

        QXmlStreamReader xml(&file);
        xml.setNamespaceProcessing(true);

        while(!xml.atEnd()) {
            QXmlStreamReader::TokenType type = xml.readNext();

            switch(type) {
            case QXmlStreamReader::StartElement:
            {
                if(xml.name().toString() == "image") {
                    QString author = xml.attributes().value("author").toString();
                    QString title = xml.attributes().value("title").toString();
                    QString filename = xml.attributes().value("filename").toString();
                    QString originalFileName = xml.attributes().value("originalFilename").toString();
                    QString uploadDateString = xml.attributes().value("uploadDate").toString();

                    QDateTime::fromString(uploadDateString);

                    LOG_DEBUG(logger, LogBuilder("adding image: title=").append(title).append(", author=").append(author).append(", filename=").append(filename));

                    memoryProvider->addImage(ImageMetadata(title, author, filename, QDateTime::fromString(uploadDateString, Qt::ISODate), originalFileName));
                }
                break;
            }
            default:
                break;
            }
            file.close();
        }
    }

}


} // namespace SJ
