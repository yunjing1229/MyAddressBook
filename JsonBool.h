#ifndef _JSONBOOL_H_
#define _JSONBOOL_H_

#include "JsonBase.h"

class JsonBool : public JsonBase
{
public:
    JsonBool(bool bValue);
    Json::Type  type() const;
    JsonBase* clone() const;
    std::string toString() const;
    bool isBool() const;
    bool asBool() const;
private:
    bool m_bValue;
};

#endif
