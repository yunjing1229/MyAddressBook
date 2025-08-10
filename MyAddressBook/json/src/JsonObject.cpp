#include "JsonObject.h"
#include <sstream>

bool JsonObject::isObject() const
{
    return true;
}


Json::Type  JsonObject::type() const
{
    return Json::JSON_OBJECT;
}

JsonBase* JsonObject::clone() const
{
    JsonObject* copy = new JsonObject();
    for (std::map<std::string, Json>::const_iterator it = m_mapValue.begin(); it != m_mapValue.end(); ++it)
    {
        copy->m_mapValue[it->first] = it->second;
    }
    return copy;
}

std::string JsonObject::toString() const
{
    std::ostringstream oss;
    oss << "{";
    for (std::map<std::string, Json>::const_iterator it = m_mapValue.begin(); it != m_mapValue.end(); ++it)
    {
        if (it != m_mapValue.begin())
        {
            oss << ",";
        }
        oss << Json(it->first).toString() << ":" << it->second.toString();
            
    }
    oss << "}";
    return oss.str();
}

Json& JsonObject::operator[](const std::string& key)
{
    std::map<std::string, Json>::iterator it = m_mapValue.find(key);
    if (it == m_mapValue.end())
    {
        throw std::runtime_error("key not found" + key);
    }
    return it->second;
  
}

size_t JsonObject::size() const
{
    return m_mapValue.size();
}

bool JsonObject::has(const std::string& key) const
{
    return m_mapValue.find(key) != m_mapValue.end();
}

void JsonObject::set(const std::string& key, const Json& value)
{
    m_mapValue[key] = value;
}