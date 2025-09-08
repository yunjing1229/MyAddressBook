#ifndef _JSONOBJECT_H_
#define _JSONOBJECT_H_
#include "JsonBase.h"
#include <map>
#include <vector>

class JsonObject : public JsonBase
{
private:
    std::map<std::string, Json> m_mapValue;
    std::vector<std::string> m_vKey;
public:
    Json::Type  type() const;
    JsonBase* clone() const;
    std::string toString() const;
    bool isObject() const;
    Json& operator[](const std::string& key);
    size_t size() const;
    bool has(const std::string& key) const;
    void set(const std::string& key, const Json& value);

};

#endif

