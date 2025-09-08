#include "JsonArray.h"
#include <sstream>


Json::Type  JsonArray::type() const
{
    return Json::JSON_ARRAY;
}

JsonBase* JsonArray::clone() const
{
    JsonArray* copy = new JsonArray();
    copy->m_arrValue.reserve(m_arrValue.size());
    for (std::vector<Json>::const_iterator it = m_arrValue.begin(); it != m_arrValue.end(); ++it)
    {
        copy->m_arrValue.push_back(*it);
    }
    return copy;
}

bool JsonArray::isArray() const
{
    return true;
}

size_t JsonArray::size() const
{
    return m_arrValue.size();
}

void JsonArray::append(const Json& value)
{
    m_arrValue.push_back(value);
}

std::string JsonArray::toString() const
{
    std::ostringstream oss;
    oss << "[";
    for (std::vector<Json>::const_iterator it = m_arrValue.begin(); it != m_arrValue.end(); ++it)
    {
        if (it != m_arrValue.begin())
        {
            oss << ",";
        }
        oss << it->toString();
    }
    oss << "]";
    return oss.str();
}

const Json& JsonArray::operator[](size_t index) const
{
    if (index > m_arrValue.size())
    {
        throw std::runtime_error("value not found");
    }
    return m_arrValue[index];
}

Json& JsonArray::operator[](size_t index)
{
    if (index > m_arrValue.size())
    {
        throw std::runtime_error("value not found");
    }
    return m_arrValue[index];
}





