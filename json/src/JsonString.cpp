#include "JsonString.h"
#include <sstream>


JsonString::JsonString(std::string strValue) : m_strValue(strValue)
{

}

JsonBase* JsonString::clone() const
{

    return new JsonString(m_strValue);
}

Json::Type  JsonString::type() const
{
    return Json::JSON_STRING;
}

bool JsonString::isString() const
{
    return true;
}

std::string JsonString::asString() const
{
    return m_strValue;
}

std::string JsonString::toString() const
{
    std::ostringstream oss;
    oss << '"';
    for (std::string::const_iterator it = m_strValue.begin(); it != m_strValue.end(); ++it)
    {
        switch (*it)
        {
        case '"': oss << "\\\""; break;
        case '\\': oss << "\\\\"; break;
        case '\b': oss << "\\\b"; break;
        case '\f': oss << "\\f"; break;
        case '\n': oss << "\\n"; break;
        case '\r': oss << "\\r"; break;
        case '\t': oss << "\\t"; break;

        default:
            if (static_cast<unsigned char>(*it) < 0x20 || *it == 0x7f)
            {
                oss << '\\u' << std::hex << std::setw(4) << std::setfill('0') << static_cast<int> (*it);
            }
            else
            {
                oss << *it;
            }
            break;
        }
    }
    oss << '"';
    return oss.str();
}