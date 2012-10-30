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


#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "httpserver.h"
#include "loggerall.h"

namespace Ui {
    class MainDialog;
}

namespace SJ {

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private:
    Ui::MainDialog *ui;
    HttpServer * server;
    bool serverStarted;
    static const Logger & logger;

private slots:
    void startButtonClickedSlot();
    void aboutButtonClickedSlot();
    void quitButtonClickedSlot();
    void settingsButtonClickedSlot();
    void handlersButtonClickedSlot();
};

} //namespace SJ

#endif // MAINDIALOG_H
