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


#ifndef SETTINGSCONSTANTS_H
#define SETTINGSCONSTANTS_H

#include <QString>

namespace SJ {

namespace ServerSettings {
const QString SETTING_WWW_ROOT_PATH = "DefaultRequestHandler/www.root.path";
const QString SETTING_LISTEN_INTERFACE = "server.listen.interface";
const QString SETTING_LISTEN_PORT = "server.listen.port";
}

namespace PluginSettings {
const QString PLUGIN_GROUP_NAME = "plugins";
const QString PLUGIN_FILE_PATH = "file.path";
const QString PLUGIN_CONTEXT_ROOT = "context.root";
const QString PLUGIN_SETTINGS_KEY = "settings.key";
}

} //namespace SJ

#endif // SETTINGSCONSTANTS_H
