#include "maindialog.h"
#include "ui_maindialog.h"
#include "logger.h"
#include "settingsconstants.h"
#include "settingsdialog.h"

#include <QSettings>
#include <QHostAddress>
#include <QMessageBox>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
    server(0)
{
    ui->setupUi(this);
    Logger::init(ui->listWidget);
    Logger::instance().debug("Logger initialized correctly");

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonClickedSlot()));
    connect(ui->aboutButton, SIGNAL(clicked()), this, SLOT(aboutButtonClickedSlot()));
    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(settingsButtonClickedSlot()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quitButtonClickedSlot()));

    server = new ImageServer(this);
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

            QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
            QString serverInterface = settings.value(SETTING_LISTEN_INTERFACE).toString();
            quint16 serverPort = settings.value(SETTING_LISTEN_PORT).toInt();

            QHostAddress adr = ImageServer::createAddress(serverInterface);

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
    QMessageBox::information(this, "About Image Server...", "Image Server written in QT by Jakub Wachowski");
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
