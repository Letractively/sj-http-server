# Introduction #

This page descirbes a logger library that is used by the SJ Http Server. The implementation is located in a separate module, thus making it easy to use in other QT projects. Source code of the library can be found here: http://code.google.com/p/sj-http-server/source/browse/#svn%2Ftrunk%2Flogger

Main features of this library are as follows:
  * loggers configurable via XML file
  * fine-grained logging levels (TRACE, DEBUG, INFO, WARN, ERROR)
  * easy log message creation by means of the LogBuilder class
  * LoggerFactory class manages loggers
  * thread safe console appender
  * thread safe file appender


# Logger configuration #

## Creating loggers via XML file ##

The simplest way to configure the logger library is to use an XML file, which will be loaded during library initialization (i.e. at the first use).
By default the file name is `sjlog.xml`, and this fiel is searched for in the current directory (so be careful where to you start your program from). The name of the file can be set explicitly by call to `LoggerFactory::loadConfig(const QString & confFile)` (be sure you call it before any logger is used).

Sample configuration file is presented below:
```
<?xml version="1.0" encoding="UTF-8" ?>
<sj:loggers xmlns:sj="http://sj-http-server.googlecode.com/logger">
    <sj:logger name="mylogger" level="DEBUG">
        <sj:appenders>
            <sj:appender type="console"/>
            <sj:appender type="file">
                <sj:appenderParam name="filename">mylog.log</sj:appenderParam>
                <sj:appenderParam name="rotated-file-timestamp-pattern">yyyy-MM-dd_hhmm</sj:appenderParam>
                <sj:appenderParam name="rotate-at-file-size-of">1048576</sj:appenderParam>
            </sj:appender>
        </sj:appenders>
    </sj:logger>
    <sj:logger name="mylogger2" level="INFO">
        <sj:appenders>
            <sj:appender type="console"/>
        </sj:appenders>
    </sj:logger>
</sj:loggers>
```

This sample configuration creates two loggers:
  1. `mylogger` which is set to `DEBUG` logging level and has two appenders:
    * console appender
    * file appender writing logs to file `mylog.log`
  1. `mylogger2` which is set to `INFO` level and prints logs to the console

## Supported Appender Parameters ##

The console appender does not support any parameters.

The file appender supports the following parameters:
  * `filename` - name and location of a file, to which logs will be written
  * `rotated-file-timestamp-pattern` - if a file is rotated, a timestamp of a given pattern is added to the file name. Pattern must comply with the `QDateTime.toStirng(PATTERN)`, for example: `'yyyy-MM-dd_hh-mm-ss-zzz'`
  * `rotate-at-file-size-of` - a maximal size of a log file; if the actual size of a file goes over this value, a file will be rotated (note that the size of a rotated file may be a bit greater than the configured value); size in bytes

## Creatig loggers via code ##

**This is a disouraged approach**. Please use the XML configuration

A sample below presents how a new logger can be created by writing just a few lines of code. For more details refer to library code (code includes doxygen comments).

```
SJ::Logger logger;
logger.addAppender(new SJ::ConsoleAppender, true);
logger.setLevel(SJ::LoggingLevel::INFO);
```

# Using loggers #

## Getting loggers ##

In order to obtain a logger one should use the `LoggerFactory` class:

```
SJ::Logger & logger = SJ::LoggerFactory::instance().getLogger("myLogger");
```

In this example _myLogger_ is the name of a logger one wishes to obtain. If name is not specified, a default logger _sj-default-logger_ will be returned. If a given logger was not defined in configuation file, then a new logger will be created with following settings:
  * logger level: INFO
  * appenders: console


## Creating log messages - LogBuilder ##

LogBuilder is a convenient class to create a log message consiting of various data types. The code below presents how to create a log message consiting of string, ints and doubles.

```
SJ::LogBuilder lb("Hello to LogBuilder.");
lb.append(" This is a string, then goes an int ").append(12);
lb.append(" and finally a double ").append(3.14);
qDebug() << lb.toString(
```

The result of this piece of code is:
```
"Hello to LogBuilder. This is a string, then goes an int 12 and finally a double 3.14"
```


## Writing log messages ##

Before sending a message to a logger one should check if a given log level is enabled (to possibly eliminate unnecessary creation of log messages). There are following functions in the `Logger` class tha are meant for this purpuse, namely"
```
bool isTraceEnabled() const;
bool isDebugEnabled() const;
bool isInfoEnabled() const;
bool isWarnEnabled() const;
bool isErrorEnabled() const;
```

To actually write a log message to an appender one of the two approaches can be used: either via functions:
```
void trace(const QString & msg, const char * filename = 0, int lineNumber = 0);
void debug(const QString & msg, const char * filename = 0, int lineNumber = 0);
void info(const QString & msg, const char * filename = 0, int lineNumber = 0);
void warn(const QString & msg, const char * filename = 0, int lineNumber = 0);
void error(const QString & msg, const char * filename = 0, int lineNumber = 0);
```

or via macros:
```
LOG_TRACE(logger,msg)
LOG_DEBUG(logger,msg)
LOG_INFO(logger,msg)
LOG_WARN(logger,msg)
LOG_ERROR(logger,msg)
```


In the first approach one only needs to specify the log message, whereas source file name and line number (indicating place where message was logged) are optional. However, it is a good practice to include this information.

In the second approach, source file name and line number are provided by the compiler, and this is the **recommended** way of logging.

For example
```
LOG_INFO(logger,"test message");
```

produces a message
```
2012-06-01 14:42:56:185 INFO [my_source_file.cpp:75] test message
```

while
```
logger.info("test message two");
```

produces
```
2012-06-01 14:42:56:185 INFO test message two
```


# Logger life cycle #

All loggers and appenders created by `LoggerFactory` are managed by it and will be destroyed when application terminates. This also applies to loggers created by means of XML configuration.

If a logger is created by a programmer, it is his/her responsibility to destroy it when it is not used anymore (as stated before - do use `LoggerFactory` )


# Limitations #

Currently there are some known limitations of the logger library. These are:
  * File Appender does not create a directory structure for its log file (file itself is created, though); if for example location of log file is defined as _logs/mylogfile.log_ make sure that the _logs_ directory exists (in the directory with the server executable);
