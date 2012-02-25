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


#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtTest/QtTest>
#include <QtCore/QSettings>

class TestSettings : public QObject
{
    Q_OBJECT

public:
    TestSettings();

private Q_SLOTS:
    void testCase1();
    void testCase2();
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



void TestSettings::testCase2()
{
    QString s1 = "/image-gallery";
    QStringList list1 = s1.split("/", QString::SkipEmptyParts);
    qDebug() << "list1 " << list1;

    QString s2 = "image-gallery";
    QStringList list2 = s2.split("/", QString::SkipEmptyParts);
    qDebug() << "list2 " << list2;

    QString s3 = "/image-gallery/foo/bar?arg=123";
    QStringList list3 = s3.split("/", QString::SkipEmptyParts);
    qDebug() << "list3 " << list3;
    list3.removeAt(0);
    QString relativePath3 = "/" + list3.join("/");
    qDebug() << "relativePath3" << relativePath3;

    QString s4 = "/image-gallery";
    QStringList list4 = s4.split("/", QString::SkipEmptyParts);
    qDebug() << "list4 " << list4;
    list4.removeAt(0);
    QString relativePath4 = "/" + list4.join("/");
    qDebug() << "relativePath4" << relativePath4;

}

QTEST_APPLESS_MAIN(TestSettings)

#include "tst_testsettings.moc"
