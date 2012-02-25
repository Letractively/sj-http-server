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


#include "settingsdialog.h"
#include "serverutils.h"
#include "settingsconstants.h"
#include <QSettings>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QHostAddress>

QSettings & AbstractSetting::settings = Utils::getSettings();

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

    AbstractSetting * wwwRootDir = new DirectorySetting("WWW root directory", SETTING_WWW_ROOT_PATH);
    connect(okButton, SIGNAL(clicked()), wwwRootDir, SLOT(saveSetting()));
    layout->addWidget(wwwRootDir);

//    IntSetting * miniatureSize = new IntSetting("Miniature size", SETTING_MINIATURE_SIZE);
//    miniatureSize->setMin(1);
//    connect(okButton, SIGNAL(clicked()), miniatureSize, SLOT(saveSetting()));
//    layout->addWidget(miniatureSize);

    AbstractSetting * interfaceHost = new HostSetting("Listening host", SETTING_LISTEN_INTERFACE);
    connect(okButton, SIGNAL(clicked()), interfaceHost, SLOT(saveSetting()));
    layout->addWidget(interfaceHost);

    IntSetting * interfacePort = new IntSetting("Listening port", SETTING_LISTEN_PORT);
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


AbstractSetting::AbstractSetting(const QString & key, QWidget * parent)
    :QWidget(parent), key(key)
{

}

BoolSetting::BoolSetting(const QString &labelText, const QString &key, QWidget * parent)
    : AbstractSetting(key, parent)
{
    checkBox = new QCheckBox();
    checkBox->setChecked(settings.value(key).toBool());

    QLabel * label = new QLabel(labelText);
    QBoxLayout * layout = new QHBoxLayout();

    layout->addWidget(label);
    layout->addWidget(checkBox);
    setLayout(layout);

}

void BoolSetting::saveSetting()
{
    settings.setValue(key, checkBox->isChecked());
}

DirectorySetting::DirectorySetting(const QString &labelText, const QString &key, QWidget * parent)
    : AbstractSetting(key, parent)
{
    QLabel * label = new QLabel(labelText);
    QBoxLayout * layout = new QHBoxLayout();

    directoryLineEdit = new QLineEdit();
    directoryLineEdit->setText(settings.value(key).toString());
    directoryLineEdit->setEnabled(false);

    QPushButton * browseButton = new QPushButton("Browse...");
    connect(browseButton, SIGNAL(clicked()), this, SLOT(browseSlot()));

    layout->addWidget(label);
    layout->addWidget(browseButton);

    QVBoxLayout * layout2 = new QVBoxLayout;
    layout2->addLayout(layout);
    layout2->addWidget(directoryLineEdit);
    setLayout(layout2);
}

void DirectorySetting::saveSetting()
{
    settings.setValue(key, directoryLineEdit->text());
}

void DirectorySetting::browseSlot()
{
    qDebug() << "lineEdit " << key << " clicked";
    QString dir = QFileDialog::getExistingDirectory(this, "Select directory...", directoryLineEdit->text());
    if(dir.endsWith("/"))  {
        directoryLineEdit->setText(dir);
    } else {
        directoryLineEdit->setText(dir + "/");
    }
}

IntSetting::IntSetting(const QString & labelText, const QString & key, QWidget * parent)
    : AbstractSetting(key, parent), minEnabled(false), maxEnabled(false)
{
    QLabel * label = new QLabel(labelText);
    intLineEdit = new QLineEdit(settings.value(key).toString());

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(intLineEdit);
    setLayout(layout);

    connect(intLineEdit, SIGNAL(textEdited(QString)), this, SLOT(valueEditedSlot()));
}

void IntSetting::saveSetting()
{
    if(isInputValid()) {
        settings.setValue(key, intLineEdit->text().toInt());
    }
}

void IntSetting::valueEditedSlot()
{
    if(!isInputValid()) {
        if(intLineEdit->graphicsEffect() == 0) {
            QGraphicsColorizeEffect * errorEffect = new QGraphicsColorizeEffect(intLineEdit);
            errorEffect->setColor(Qt::red);
            intLineEdit->setGraphicsEffect(errorEffect);
        }
    } else {
        if(intLineEdit->graphicsEffect() != 0) {
            delete intLineEdit->graphicsEffect();
            intLineEdit->setGraphicsEffect(0);
        }
    }

}
bool IntSetting::isInputValid()
{
    QString val = intLineEdit->text();
    bool ok = false;
    int v = val.toInt(&ok);

    if(ok && minEnabled) {
        if(v < min) {
            ok = false;
        }
    }

    if(ok && maxEnabled) {
        if(v > max) {
            ok = false;
        }
    }
    return ok;
}

void IntSetting::setMin(int v)
{
    minEnabled = true;
    min = v;
}

void IntSetting::setMax(int v)
{
    maxEnabled = true;
    max = v;
}

HostSetting::HostSetting(const QString & labelText, const QString & key, QWidget * parent)
    : AbstractSetting(key, parent)
{
    QLabel * label = new QLabel(labelText);
    hostLineEdit = new QLineEdit(settings.value(key).toString());

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(hostLineEdit);
    setLayout(layout);

    connect(hostLineEdit, SIGNAL(textEdited(QString)), this, SLOT(valueEditedSlot()));
}

void HostSetting::saveSetting()
{
    if(isInputValid()) {
        settings.setValue(key, hostLineEdit->text());
    }
}

bool HostSetting::isInputValid()
{
    QString text = hostLineEdit->text().trimmed();
    if("any" == text || "localhost" == text || "127.0.0.1" == text) {
        return true;
    }

    QHostAddress adr = QHostAddress(hostLineEdit->text());
    if(adr.isNull()) {
        return false;
    }

    return true;
}

void HostSetting::valueEditedSlot()
{
    if(!isInputValid()) {
        if(hostLineEdit->graphicsEffect() == 0) {
            QGraphicsColorizeEffect * errorEffect = new QGraphicsColorizeEffect(hostLineEdit);
            errorEffect->setColor(Qt::red);
            hostLineEdit->setGraphicsEffect(errorEffect);
        }
    } else {
        if(hostLineEdit->graphicsEffect() != 0) {
            delete hostLineEdit->graphicsEffect();
            hostLineEdit->setGraphicsEffect(0);
        }
    }

}


