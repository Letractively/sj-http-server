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

#ifndef HANDLERCONFIGURATION_H
#define HANDLERCONFIGURATION_H

#include <QMap>
#include <QString>
#include <QVariant>

namespace SJ {
class HandlerConfiguration
{

public:
    HandlerConfiguration();
    HandlerConfiguration(const QString & name, const QString & description, const QString & contextRoot,
                         const QString & filePath, const QMap<QString, QVariant> & initParams);

    QString getName() const { return name; }
    QString getDescription() const { return description; }
    QString getContextRoot() const { return contextRoot; }
    QString getFilePath() const { return filePath; }
    const QMap<QString, QVariant> & getInitParams() const { return initParams; }

protected:
    QString name;
    QString description;
    QString contextRoot;
    QString filePath;
    QMap<QString, QVariant> initParams;
};
}
#endif // HANDLERCONFIGURATION_H
