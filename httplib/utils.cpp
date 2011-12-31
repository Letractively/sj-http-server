#include "utils.h"


QString Utils::substring(const QString & str, int beginIndex, int endIndex)
{
    if(endIndex == -1) {
        return str.mid(beginIndex, endIndex);
    } else {
        return str.mid(beginIndex, str.length() - beginIndex - endIndex);
    }
}
