#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QSettings>
#include <QCheckBox>
#include <QLineEdit>
#include <QGraphicsColorizeEffect>

class AbstractSetting : public QWidget
{
    Q_OBJECT

public slots:
    virtual void saveSetting() = 0;
protected:
    AbstractSetting(const QString & key, QWidget * parent = 0);
    QString key;
    static QSettings settings;

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

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);

signals:

public slots:

private slots:
    void okSlot();


};

#endif // SETTINGSDIALOG_H
