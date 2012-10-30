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


#ifndef SETTINGWIDGETSFACTORY_H
#define SETTINGWIDGETSFACTORY_H

#include <QSettings>
#include <QString>
#include <QCheckBox>
#include <QLineEdit>

#include "settingsitem.h"

namespace SJ {

class AbstractSetting : public QWidget
{
    Q_OBJECT

public slots:
    virtual void saveSetting() = 0;
protected:
    AbstractSetting(const QString & key, QWidget * parent = 0);
    QString key;
    static QSettings & settings;
};


class BoolSetting : public AbstractSetting
{
    Q_OBJECT
public:
    BoolSetting(const QString & labelText, const QString & key, QWidget * parent = 0);
public slots:
    virtual void saveSetting();
private:
    QCheckBox * checkBox;
};

class DirectorySetting : public AbstractSetting
{
    Q_OBJECT
public:
    DirectorySetting(const QString & labelText, const QString & key, QWidget * parent = 0);
public slots:
    virtual void saveSetting();
private:
    QLineEdit * directoryLineEdit;
private slots:
    void browseSlot();
};

class HostSetting : public AbstractSetting
{
    Q_OBJECT
public:
    HostSetting(const QString & labelText, const QString & key, QWidget * parent = 0);
public slots:
    virtual void saveSetting();
private:
    QLineEdit * hostLineEdit;
    bool isInputValid();
private slots:
    void valueEditedSlot();
};


class IntSetting : public AbstractSetting
{
    Q_OBJECT
public:
    IntSetting(const QString & labelText, const QString & key, QWidget * parent = 0);
    void setMin(int);
    void setMax(int);
public slots:
    virtual void saveSetting();
private:
    QLineEdit * intLineEdit;
    int min;
    int max;
    bool minEnabled;
    bool maxEnabled;

    bool isInputValid();
private slots:
    void valueEditedSlot();
};

class StringSetting : public AbstractSetting
{
    Q_OBJECT
public:
    StringSetting(const QString & labelText, const QString & key, QWidget * parent = 0);
public slots:
    virtual void saveSetting();
private:
    QLineEdit * stringLineEdit;
    bool isInputValid();
private slots:
    void valueEditedSlot();
};


class SettingWidgetsFactory
{
    SettingWidgetsFactory();
public:
    static AbstractSetting * getWidget(SettingsItem::SettingType type, const QString & key, const QString & labelText, QWidget *parent = 0);
};

} //namespace SJ

#endif // SETTINGWIDGETSFACTORY_H
