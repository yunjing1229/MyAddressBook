#ifndef _JSONNUMBER_H_
#define _JSONNUMBER_H_

#include "JsonBase.h"

class JsonNumber : public JsonBase
{
private:
    double m_nValue;
public:
    JsonNumber(double numValue);
    Json::Type type() const;
    JsonBase* clone() const;
    std::string toString() const;
    bool isNumber() const;
    double asDouble() const;
    int asInt() const;
};

#endif

