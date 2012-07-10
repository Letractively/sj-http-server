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


#include "handlersdialog.h"
#include "handlermanager.h"

#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "settingsconstants.h"

namespace SJ {

HandlerEditor::HandlerEditor(HandlerData * handler, QWidget * parent)
    : QWidget(parent), handler(handler)
{

    QLabel * nameLabel = new QLabel(handler->getHandler()->name(), this);
    contextPathSetting = new StringSetting("Context Path", handler->getSettingsGroup() + "/" + PluginSettings::PLUGIN_CONTEXT_ROOT);
    connect(this, SIGNAL(okSignal()), contextPathSetting, SLOT(saveSetting()));
    QHBoxLayout * layout = new QHBoxLayout;

    layout->addWidget(nameLabel);
    layout->addWidget(contextPathSetting);



    QVector<SettingsItem> sets = handler->getHandler()->supportedSettings();
    for(int k = 0; k < sets.size(); ++k) {
        AbstractSetting * setting = SettingWidgetsFactory::getWidget(sets.at(k).getType(),
                                    handler->getSettingsGroup() + "/" + sets.at(k).getKey(), sets.at(k).getName());
        if(0 != setting) {
            allSettings.push_back(setting);
            connect(this, SIGNAL(okSignal()), setting, SLOT(saveSetting()));
            layout->addWidget(setting);
        } else {
//            error
        }
    }

    setLayout(layout);
}

//QString HandlerEditor::nameToContextRoot(const QString & name)
//{
//    QString s = name;
//    s = s.replace(' ', '-');
//    s = s.replace('\t', '-');
//    s = s.replace('\n', '-');

//    return s.toLower();
//}

void HandlerEditor::okSlot()
{/*
    contextPathSetting->saveSetting();
    for(int i = 0; i < allSettings.size(); ++i) {
        allSettings[i]->saveSetting();
    }*/
    emit okSignal();
}

HandlerEditor::~HandlerEditor() {
    delete contextPathSetting;
    for(int i = 0; i < allSettings.size(); ++i) {
        delete allSettings[i];
    }
}


HandlersDialog::HandlersDialog(QWidget *parent) :
    QDialog(parent)
{
    qDebug() << "registered handlers are: ";
    QVector<HandlerData> * handlers = HandlerManager::instance().getAllHandlers();
    for(int i = 0; i < handlers->size(); ++i) {
        qDebug() << "Name: " << handlers->at(i).getHandler()->name() << ", context: " << handlers->at(i).getContextRoot();
    }

    QPushButton * closeButton = new QPushButton("Close");
    QPushButton * okButton = new QPushButton("Ok");

    QVBoxLayout * layout = new QVBoxLayout;

    for(int i = 0; i < handlers->size(); ++i) {
        HandlerEditor * e = new HandlerEditor(&(handlers->operator [](i)));
        connect(okButton, SIGNAL(clicked()), e, SLOT(okSlot()));
        layout->addWidget(e);
    }

    QHBoxLayout * buttonsBox = new QHBoxLayout;
    buttonsBox->addWidget(okButton);
    buttonsBox->addWidget(closeButton);

    layout->addLayout(buttonsBox);

    setLayout(layout);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
}

} // namespace SJ
