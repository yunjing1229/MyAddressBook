#ifndef _JSONARRAY_H_
#define _JSONARRAY_H_
#include "JsonBase.h"
#include <vector>

class JsonArray : public JsonBase
{
private:
    std::vector<Json> m_arrValue;
public:
    Json::Type  type() const;
    JsonBase* clone() const;
    std::string toString() const;
    bool isArray() const;
    const Json& operator[](size_t index) const;
    Json& operator[](size_t index);
    size_t size() const;
    void append(const Json& value);
};

#endif

