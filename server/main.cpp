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


#include <QtWidgets/QApplication>
#include <QSettings>
#include "maindialog.h"
#include "settingsconstants.h"
#include "serverutils.h"

#include "loggerfactory.h"
#include "logbuilder.h"

static void setUpSettings();
static QString copyrightNote();

int main(int argc, char *argv[])
{
    SJ::Logger & logger = SJ::LoggerFactory::instance().getLogger("sj-server-logger");

    LOG_INFO(logger,copyrightNote());
    setUpSettings();

    QApplication a(argc, argv);

    SJ::MainDialog w;
    w.show();

    return a.exec();
}


void setUpSettings()
{
    QSettings & settings = SJ::Utils::getSettings();

    //setup default values

    if(!settings.contains(SJ::ServerSettings::SETTING_LISTEN_INTERFACE)) {
        settings.setValue(SJ::ServerSettings::SETTING_LISTEN_INTERFACE, "localhost");
    }

    if(!settings.contains(SJ::ServerSettings::SETTING_LISTEN_PORT)) {
        settings.setValue(SJ::ServerSettings::SETTING_LISTEN_PORT, 9090);
    }

    if(!settings.contains(SJ::ServerSettings::SETTING_WWW_ROOT_PATH)) {
        settings.setValue(SJ::ServerSettings::SETTING_WWW_ROOT_PATH, "/var/www/");
    }

    SJ::Logger & logger = SJ::LoggerFactory::instance().getLogger("sj-server-logger");
    if(logger.isDebugEnabled()) {
        SJ::LogBuilder lb("Settings:\n");
        QStringList allKeys = settings.allKeys();
        for(int i = 0; i < allKeys.size(); ++i) {
            lb.append("key ").append(allKeys[i]).append(". value: ");
            lb.append(settings.value(allKeys[i]).toString()).append("\n");
        }
        LOG_DEBUG(logger, lb);
    }
}


QString copyrightNote()
{
    QString copyright = "http://sj-http-server.googlecode.com/\n\n"
            "Copyright (C) 2011-2012  Jakub Wachowski\n\n"

            "This program is free software: you can redistribute it and/or modify\n"
            "it under the terms of the GNU General Public License as published by\n"
            "the Free Software Foundation, either version 3 of the License, or\n"
            "any later version.\n\n"

            "This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
            "GNU General Public License for more details.\n\n"

            "You should have received a copy of the GNU General Public License\n"
            "along with this program. If not, see <http://www.gnu.org/licenses/>.\n\n";

    return copyright;
}
