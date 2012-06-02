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


#ifndef LOGBUILDER_H
#define LOGBUILDER_H

#include <QString>
#include <QVariant>
#include <QStringList>

namespace SJ {


/**
  @brief LogBuilder facilitates creation of log messages. Can be used to produce a QString object from different
  types (like ints or doubles)
  */
class LogBuilder
{
public:

    /**
      @brief Constructs LogBuilder and optionally initializes it with given QString

      @param msg Initial content of LogBuilder
      */
    LogBuilder(const QString & msg = "");

    /**
      @brief Constructs LogBuilder and adds all strings from list to its content

      By defautl strings from list are concatinated without any separator (controllable by the second argument)

      @param stringList list of strings used as initial content of LogBuilder
      @param separator string that would separate each string from list when appending to LogBuilder (empty by default)
      */
    LogBuilder(const QStringList & stringList, const QString & separator = "");


    /**
      @brief appends a string list to LogBuilder
      @param stringList list of strings to be appended
      @param separator string that would separate each string from list when appending to LogBuilder (empty by default)
      @return reference to the same LogBuilder
      */
    LogBuilder & append(const QStringList & stringList, const QString & separator = "");

    /**
      @brief appends a string to LogBuilder
      @param string string to be appended
      @return reference to the same LogBuilder
      */
    LogBuilder & append(const QString & s);

    /**
      @brief appends a C-string to LogBuilder
      @param s C-string to be appended
      @return reference to the same LogBuilder
      */
    LogBuilder & append(const char * s);


    /**
      @brief appends any type to LogBuilder

      It is required that type is supported by the QVariant object

      @param t variale to be appended
      @return reference to the same LogBuilder
      */
    template <typename T> LogBuilder & append(T t)
    {
        QVariant v = t;
        list.append(v.toString());
        return *this;
    }


    /**
      @brief Returns string representation of a LogBuilder (i.e. all appended values)
      @return log message as a string
      */
    QString toString() const;

    /**
      @breif conversion function - automatically converts LogBuilder to QString
      */
    operator QString() const;

    /**
      @brief removes all content of a LogBuilder
      */
    void clear();

private:
    QStringList list;
};

} // namespace SJ

#endif // LOGBUILDER_H
