#include <QtGui/QApplication>
#include <QSettings>
#include <QDebug>
#include "maindialog.h"
#include "settingsconstants.h"

static void setUpSettings();

int main(int argc, char *argv[])
{
    setUpSettings();
    QApplication a(argc, argv);

    MainDialog w;
    w.show();

    return a.exec();
}


void setUpSettings()
{

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);


    //setup default values
    if(!settings.contains(SETTING_FILE_STORE_PATH)) {
        settings.setValue(SETTING_FILE_STORE_PATH, "/tmp/");
    }

    if(!settings.contains(SETTING_MINIATURE_ENABLED)) {
        settings.setValue(SETTING_MINIATURE_ENABLED, true);
    }

    if(!settings.contains(SETTING_MINIATURE_SIZE)) {
        settings.setValue(SETTING_MINIATURE_SIZE, 256);
    }

    if(!settings.contains(SETTING_LISTEN_INTERFACE)) {
        settings.setValue(SETTING_LISTEN_INTERFACE, "localhost");
    }

    if(!settings.contains(SETTING_LISTEN_PORT)) {
        settings.setValue(SETTING_LISTEN_PORT, 9090);
    }

    if(!settings.contains(SETTING_WWW_ROOT_PATH)) {
        settings.setValue(SETTING_WWW_ROOT_PATH, "/var/www/");
    }

    qDebug() << "Settings:";
    qDebug() << SETTING_FILE_STORE_PATH <<  " = " << settings.value(SETTING_FILE_STORE_PATH).toString();
    qDebug() << SETTING_MINIATURE_ENABLED <<  " = " << settings.value(SETTING_MINIATURE_ENABLED).toBool();
    qDebug() << SETTING_MINIATURE_SIZE <<  " = " << settings.value(SETTING_MINIATURE_SIZE).toInt();
    qDebug() << SETTING_LISTEN_INTERFACE <<  " = " << settings.value(SETTING_LISTEN_INTERFACE).toString();
    qDebug() << SETTING_LISTEN_PORT <<  " = " << settings.value(SETTING_LISTEN_PORT).toInt();
    qDebug() << SETTING_WWW_ROOT_PATH <<  " = " << settings.value(SETTING_WWW_ROOT_PATH).toString();
}
