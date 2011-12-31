#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "imageserver.h"

namespace Ui {
    class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private:
    Ui::MainDialog *ui;
    ImageServer * server;
    bool serverStarted;

private slots:
    void startButtonClickedSlot();
    void aboutButtonClickedSlot();
    void quitButtonClickedSlot();
    void settingsButtonClickedSlot();
};

#endif // MAINDIALOG_H
