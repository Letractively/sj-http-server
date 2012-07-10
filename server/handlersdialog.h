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


#ifndef HANDLERSDIALOG_H
#define HANDLERSDIALOG_H

#include <QDialog>
#include "handlerdata.h"
#include "settingwidgetsfactory.h"

namespace SJ {

class HandlerEditor : public QWidget
{
    Q_OBJECT
public:
    explicit HandlerEditor(HandlerData * handler, QWidget * parent = 0);
    ~HandlerEditor();
private:

//    QString nameToContextRoot(const QString & name);

    HandlerData * handler;
    StringSetting * contextPathSetting;
    QVector<AbstractSetting *> allSettings;


private slots:
    void okSlot();
signals:
    void okSignal();
};


class HandlersDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HandlersDialog(QWidget *parent = 0);

signals:

public slots:

};

} //namespace SJ

#endif // HANDLERSDIALOG_H
