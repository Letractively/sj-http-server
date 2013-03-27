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


#include "settingsconstants.h"
#include "serverutils.h"
#include "httpserver.h"

#include "loggerfactory.h"
#include "logbuilder.h"

#include <QCoreApplication>
#include <cstdlib>
#include <signal.h>

#include "configurationprovider.h"
#include "mockconfigurationprovider.h"

using namespace SJ;

static ConfigurationProvider initConfiguration();
static void signalHandler(int signal);
static void close();
static QString copyrightNote();

static HttpServer * server = 0;
static Logger & logger = SJ::LoggerFactory::instance().getLogger("sj-server-logger");

int main(int argc, char *argv[])
{
    signal(SIGINT, signalHandler);

    QCoreApplication a(argc, argv);
    ConfigurationProvider conf = initConfiguration();

    LOG_INFO(logger,copyrightNote());

    server = new HttpServer;
    bool started = server->listen(conf.getListenInterface(), conf.getListenPort());
    if(!started) {
        LOG_ERROR(logger, "server not started");
        LOG_ERROR(logger, server->errorString());
        return -1;
    } else {
        LOG_INFO(logger, "server started");
    }

    return a.exec();
}


ConfigurationProvider initConfiguration()
{
    return MockConfigurationProvider();
}

void close() {
    LOG_INFO(logger, "Closing the application...");
    if(server != 0) {
        server->close();
        server = 0;
    }
    LOG_INFO(logger, "Shutdown completed");
}


void signalHandler(int signal)
{
    switch(signal) {
    case SIGINT : close();
        exit(0);
        break;
    }
}

QString copyrightNote()
{
    QString copyright = "\n"
            "http://sj-http-server.googlecode.com/\n\n"
            "Copyright (C) Jakub Wachowski\n\n"

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

