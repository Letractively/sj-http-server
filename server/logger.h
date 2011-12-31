#ifndef LOGGER_H
#define LOGGER_H

#include "QListWidget"

const int LOGGER_BUFFER_SIZE = 100;

class Logger
{
public:
    static Logger & instance();
    static void init(QListWidget * loggerWidget);
    void debug(const QString & str);
private:
    void log(const QString & str);
    Logger(QListWidget * loggerWidget);
    QListWidget * loggerWidget;
    static Logger * logger;
};

#endif // LOGGER_H
