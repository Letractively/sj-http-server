/*
http://sj-http-server.googlecode.com/

Copyright (C) 2011-2012  Samir Jorina

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

class SettingsItem
{
public:
    enum SettingType {INT, BOOL, STRING, DIRECTORY};

    SettingsItem();
    SettingsItem(const QString & name, const SettingType & type);
    const QString & getName() { return name; }
    const SettingType & getType() { return type; }
    void setName(const QString & name) { this->name = name; }
    void setType(const SettingType & type) { this->type = type; }

private:
    QString name;
    SettingType type;
};

#endif // SETTINGSITEM_H
