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


#ifndef SETTINGSITEM_H
#define SETTINGSITEM_H

#include <QString>

namespace SJ {

class SettingsItem
{
public:
    enum SettingType {INT, BOOL, STRING, DIRECTORY};

    SettingsItem();
    SettingsItem(const QString & name, const SettingType & type, const QString & key);
    const QString & getName() const { return name; }
    const SettingType & getType() const { return type; }
    const QString & getKey() const { return key; }

private:
    QString name;
    SettingType type;
    QString key;
};

} //namespace SJ

#endif // SETTINGSITEM_H
