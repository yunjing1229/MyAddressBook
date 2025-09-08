#ifndef _JSONSTRING_H_
#define _JSONSTRING_H_

#include "JsonBase.h"
#include <iomanip>

class JsonString :  public JsonBase
{
public:
    JsonString(std::string strValue);
    Json::Type  type() const;
    JsonBase* clone() const;
    std::string toString() const;
    bool isString() const;
    std::string asString() const;
private:
    std::string m_strValue;
};

#endif

