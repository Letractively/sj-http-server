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


#ifndef HANDLERSDIALOG_H
#define HANDLERSDIALOG_H

#include <QDialog>
#include "handlerdata.h"

class HandlerEditor : public QWidget
{
    Q_OBJECT
public:
    explicit HandlerEditor(HandlerData * handler, QWidget * parent = 0);
private:

    QString nameToContextRoot(const QString & name);

    HandlerData * handler;

private slots:
    void contextRootChangedSlot(const QString & contextRoot);
};


class HandlersDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HandlersDialog(QWidget *parent = 0);

signals:

public slots:

};

#endif // HANDLERSDIALOG_H
