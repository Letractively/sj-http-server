#ifndef FORTUNETELLER_H
#define FORTUNETELLER_H

#include <abstractrequesthandler.h>
#include <QObject>
#include <QVector>

class FortuneTeller : public QObject, public AbstractRequestHandler
{
    Q_OBJECT
    Q_INTERFACES(AbstractRequestHandler)
public:
    QString name();
    HttpResponse handle(HttpRequest *req, QSettings *settings);
private:
    static QVector<QString> fortunes;
    static bool fortunesSet;
    static QString getFortune();
};

#endif // FORTUNETELLER_H
