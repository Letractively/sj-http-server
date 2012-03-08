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

#include "settingwidgetsfactory.h"

HandlerEditor::HandlerEditor(HandlerData * handler, QWidget * parent)
    : QWidget(parent), handler(handler)
{

    QString cr = handler->getContextRoot();
    if("" == cr) {
        cr = nameToContextRoot(handler->getHandler()->name());
    }
    QLineEdit * contextRootEdit = new QLineEdit(cr);
    QLabel * nameLabel = new QLabel(handler->getHandler()->name());



    QHBoxLayout * layout = new QHBoxLayout;

    layout->addWidget(nameLabel);
    layout->addWidget(contextRootEdit);

    setLayout(layout);

    connect(contextRootEdit, SIGNAL(textChanged(QString)), this, SLOT(contextRootChangedSlot(QString)));

}

QString HandlerEditor::nameToContextRoot(const QString & name)
{
    QString s = name;
    s = s.replace(' ', '-');
    s = s.replace('\t', '-');
    s = s.replace('\n', '-');

    return s.toLower();
}

void HandlerEditor::contextRootChangedSlot(const QString & contextRoot)
{
    handler->setContextRoot(contextRoot);
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

    QVBoxLayout * layout = new QVBoxLayout;

    for(int i = 0; i < handlers->size(); ++i) {
        HandlerEditor * e = new HandlerEditor(&(handlers->operator [](i)));
        layout->addWidget(e);
        QVector<SettingsItem> sets = handlers->at(i).getHandler()->supportedSettings();
        for(int k = 0; k < sets.size(); ++k) {
            layout->addWidget(SettingWidgetsFactory::getWidget(sets.at(k).getType(),
                                    handlers->at(i).getSettingsGroup() + "/" + sets.at(k).getKey(), sets.at(k).getName()));
        }
    }

    layout->addWidget(closeButton);
    setLayout(layout);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

}
