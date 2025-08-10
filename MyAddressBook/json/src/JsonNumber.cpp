#include "JsonNumber.h"
#include <sstream>

Json::Type JsonNumber::type() const
{
    return Json::JSON_NUMBER;
}

JsonNumber::JsonNumber(double nValue): m_nValue(nValue)
{

}

JsonBase* JsonNumber::clone() const
{
    return new JsonNumber(m_nValue);
}

std::string JsonNumber::toString() const
{
    std::ostringstream oss;
    oss << m_nValue;
    return oss.str();
}

bool JsonNumber::isNumber() const
{
    return true;
}

double JsonNumber::asDouble() const
{
    return m_nValue;
}

int JsonNumber::asInt() const
{
    return static_cast<int>(m_nValue);
}