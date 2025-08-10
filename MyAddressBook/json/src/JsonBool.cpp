#include "JsonBool.h"

JsonBool::JsonBool(bool bValue) : m_bValue(bValue)
{

}

Json::Type  JsonBool::type() const
{
    return Json::JSON_BOOL;
}

JsonBase* JsonBool::clone() const
{

    return new JsonBool(m_bValue);
}

std::string JsonBool::toString() const
{
    return m_bValue ? "true" : "false";
}

bool JsonBool::isBool() const
{
    return true;
}

bool JsonBool::asBool() const
{
    return m_bValue;
}