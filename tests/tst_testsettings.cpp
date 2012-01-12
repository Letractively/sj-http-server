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


#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QSettings>

class TestSettings : public QObject
{
    Q_OBJECT

public:
    TestSettings();

private Q_SLOTS:
    void testCase1();
};

TestSettings::TestSettings()
{
}



void TestSettings::testCase1()
{
    QSettings settings("sj-http-server-test.ini", QSettings::IniFormat);

    settings.setValue("key1", "val1");
    settings.setValue("group/key2", "value2");

    settings.beginWriteArray("plugins");

    settings.setArrayIndex(0);
    settings.setValue("location", "/home/user/sj-plugins/libplugin.so");
    settings.setValue("context.path", "plugin-context");

    settings.setArrayIndex(1);
    settings.setValue("location", "/home/user/sj-plugins/libplugin2.so");
    settings.setValue("context.path", "plugin2-context");

    settings.endArray();

    settings.sync();


}

QTEST_APPLESS_MAIN(TestSettings)

#include "tst_testsettings.moc"
