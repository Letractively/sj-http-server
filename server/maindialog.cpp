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


#include "maindialog.h"
#include "ui_maindialog.h"
#include "logger.h"
#include "settingsconstants.h"
#include "settingsdialog.h"
#include "serverutils.h"
#include "handlersdialog.h"

#include <QSettings>
#include <QHostAddress>
#include <QMessageBox>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
    server(0),
    serverStarted(false)
{
    ui->setupUi(this);
    setWindowTitle("SJ-Server v. " + Utils::version());
    Logger::init(ui->listWidget);
    Logger::instance().debug("Logger initialized correctly");

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonClickedSlot()));
    connect(ui->aboutButton, SIGNAL(clicked()), this, SLOT(aboutButtonClickedSlot()));
    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(settingsButtonClickedSlot()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quitButtonClickedSlot()));
    connect(ui->handlersButton, SIGNAL(clicked()), this, SLOT(handlersButtonClickedSlot()));

    server = new HttpServer(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}



void MainDialog::startButtonClickedSlot()
{

    if(server != 0) {
        if(!serverStarted) {
            Logger::instance().debug("Starting server...");

            QSettings & settings = Utils::getSettings();
            QString serverInterface = settings.value(SETTING_LISTEN_INTERFACE).toString();
            quint16 serverPort = settings.value(SETTING_LISTEN_PORT).toInt();

            QHostAddress adr = HttpServer::createAddress(serverInterface);

            qDebug() << "adr = " << adr << ", port = " << serverPort;

            server->listen(adr, serverPort);
            if(!server->isListening())
            {
                Logger::instance().debug("Cannot start the server");
                Logger::instance().debug(server->errorString());
            } else {
                ui->startButton->setText("Stop server");
                serverStarted = true;
                Logger::instance().debug("Server listening on " + serverInterface + ":" + settings.value(SETTING_LISTEN_PORT).toString());
            }
        } else {
            Logger::instance().debug("Stopping server...");
            server->close();
            if(server->isListening())
            {
                Logger::instance().debug("Cannot stop the server");
                Logger::instance().debug(server->errorString());
            } else {
                ui->startButton->setText("Start server");
                serverStarted = false;
                Logger::instance().debug("Server stopped");
            }

        }
    } else {
        Logger::instance().debug("Error - cannot run the server. Please restart the application");
    }
}

void MainDialog::aboutButtonClickedSlot()
{
    QMessageBox::information(this, "About Server...", "Http Server written in Qt by Samir Jorina\nhttp://sj-http-server.googlecode.com/");
}

void MainDialog::quitButtonClickedSlot()
{
    if(server != 0 && server->isListening()) {
        server->close();
        delete server;
        server = 0;
    }

    this->close();

}

void MainDialog::settingsButtonClickedSlot()
{
    SettingsDialog dialog;
    dialog.exec();
}

void MainDialog::handlersButtonClickedSlot() {
    HandlersDialog dialog;
    dialog.exec();
}
