#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
    static QString substring(const QString & str, int beginIndex, int endIndex = -1);
};

#endif // UTILS_H
