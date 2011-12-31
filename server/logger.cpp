#include "logger.h"
#include "maindialog.h"
#include <QDateTime>

Logger * Logger::logger;

void Logger::init(QListWidget *loggerWidget)
{
    if(0 == logger) {
        logger = new Logger(loggerWidget);
    } else {
        //error
    }
}

Logger & Logger::instance()
{
    if(0 == logger) {
        //error
    }
    return *logger;
}

Logger::Logger(QListWidget * loggerWidget)
    : loggerWidget(loggerWidget)
{
}

void Logger::log(const QString &str)
{
    if(loggerWidget->count() > LOGGER_BUFFER_SIZE) {
        delete loggerWidget->takeItem(0);
    }
    QDateTime currentTime = QDateTime::currentDateTime();
    QString logMessage = currentTime.toString("yyyy-MM-dd HH:mm:ss.zzz ") + str;
    loggerWidget->addItem(logMessage);
    loggerWidget->setCurrentRow(loggerWidget->count() - 1);
}

void Logger::debug(const QString &str)
{
    //if enabled
    log(str);
}


