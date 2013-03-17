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


#include "settingsdialog.h"
#include "serverutils.h"
#include "settingsconstants.h"
#include "settingwidgetsfactory.h"

#include <QSettings>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QHostAddress>

namespace SJ {

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Settings");
    QBoxLayout * layout = new QVBoxLayout();

    QPushButton * cancelButton = new QPushButton("Cancel");
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    QPushButton * okButton = new QPushButton("Ok");
    connect(okButton, SIGNAL(clicked()), this, SLOT(okSlot()));

    QLabel * label = new QLabel("Settings");


    layout->addWidget(label);

//    AbstractSetting * genMiniatures = new BoolSetting("Generate miniatures", SETTING_MINIATURE_ENABLED);
//    connect(okButton, SIGNAL(clicked()), genMiniatures, SLOT(saveSetting()));
//    layout->addWidget(genMiniatures);

//    AbstractSetting * fileStoreDir = new DirectorySetting("File storage directory", SETTING_FILE_STORE_PATH);
//    connect(okButton, SIGNAL(clicked()), fileStoreDir, SLOT(saveSetting()));
//    layout->addWidget(fileStoreDir);

    AbstractSetting * wwwRootDir = new DirectorySetting("WWW root directory", ServerSettings::SETTING_WWW_ROOT_PATH);
    connect(okButton, SIGNAL(clicked()), wwwRootDir, SLOT(saveSetting()));
    layout->addWidget(wwwRootDir);

//    IntSetting * miniatureSize = new IntSetting("Miniature size", SETTING_MINIATURE_SIZE);
//    miniatureSize->setMin(1);
//    connect(okButton, SIGNAL(clicked()), miniatureSize, SLOT(saveSetting()));
//    layout->addWidget(miniatureSize);

    AbstractSetting * interfaceHost = new HostSetting("Listening host", ServerSettings::SETTING_LISTEN_INTERFACE);
    connect(okButton, SIGNAL(clicked()), interfaceHost, SLOT(saveSetting()));
    layout->addWidget(interfaceHost);

    IntSetting * interfacePort = new IntSetting("Listening port", ServerSettings::SETTING_LISTEN_PORT);
    interfacePort->setMin(1);
    interfacePort->setMax(99999);
    connect(okButton, SIGNAL(clicked()), interfacePort, SLOT(saveSetting()));
    layout->addWidget(interfacePort);

    layout->addWidget(cancelButton);
    layout->addWidget(okButton);

    setLayout(layout);
}

void SettingsDialog::okSlot()
{
    //save settings

    close();
}

} //namespace SJ



