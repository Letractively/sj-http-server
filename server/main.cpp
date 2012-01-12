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


#include <QtGui/QApplication>
#include <QSettings>
#include <QDebug>
#include "maindialog.h"
#include "settingsconstants.h"
#include "utils.h"

static void setUpSettings();
static QString copyrightNote();

int main(int argc, char *argv[])
{
    qDebug() << copyrightNote();
    setUpSettings();

    QApplication a(argc, argv);

    MainDialog w;
    w.show();

    return a.exec();
}


void setUpSettings()
{
    QSettings & settings = Utils::getSettings();

    //setup default values

    if(!settings.contains(SETTING_LISTEN_INTERFACE)) {
        settings.setValue(SETTING_LISTEN_INTERFACE, "localhost");
    }

    if(!settings.contains(SETTING_LISTEN_PORT)) {
        settings.setValue(SETTING_LISTEN_PORT, 9090);
    }

    if(!settings.contains(SETTING_WWW_ROOT_PATH)) {
        settings.setValue(SETTING_WWW_ROOT_PATH, "/var/www/");
    }

    qDebug() << "Settings:";
    qDebug() << SETTING_LISTEN_INTERFACE <<  " = " << settings.value(SETTING_LISTEN_INTERFACE).toString();
    qDebug() << SETTING_LISTEN_PORT <<  " = " << settings.value(SETTING_LISTEN_PORT).toInt();
    qDebug() << SETTING_WWW_ROOT_PATH <<  " = " << settings.value(SETTING_WWW_ROOT_PATH).toString();
}


QString copyrightNote()
{
    QString copyright = "http://sj-http-server.googlecode.com/\n\n"
            "Copyright (C) 2011-2012  Samir Jorina\n\n"

            "This program is free software: you can redistribute it and/or modify\n"
            "it under the terms of the GNU General Public License as published by\n"
            "the Free Software Foundation, either version 3 of the License, or\n"
            "(at your option) any later version.\n\n"

            "This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "GNU General Public License for more details.\n\n"

            "You should have received a copy of the GNU General Public License\n"
            "along with this program. If not, see <http://www.gnu.org/licenses/>.\n\n";

    return copyright;
}
