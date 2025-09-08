#include "Json.h"
#include "JsonString.h"
#include "JsonObject.h"
#include "JsonBool.h"
#include "JsonArray.h"
#include "JsonNumber.h"
#include "JsonParser.h"
#include "JsonBase.h"



std::string Json::toString() const
{
  return m_pValue->toString();
}

Json::Json()
{

}

Json::Json(double fValue) : m_pValue(new JsonNumber(fValue))
{

}

Json::Json(int nValue) : m_pValue(new JsonNumber(nValue))
{

}


Json::Json(const std::string& str)
{
    m_pValue = new JsonString(str);
}

Json::Json(const char* str)
{
    m_pValue = new JsonString(str);
}

Json::Json(bool bValue) : m_pValue(new JsonBool(bValue))
{

}

Json::Json(JsonBase* pValue) : m_pValue(pValue)
{

}

Json Json::Object()
{
    return Json(new JsonObject());
}

Json Json::Array()
{
   return Json(new JsonArray());
}

Json Json::Parse(const std::string& str)
{
    JsonParser parse(str);
    return parse.parseValue();

}

void Json::set(const std::string& strKey, const Json& value)
{
    m_pValue->set(strKey, value);
}

void Json::append(const Json& value)
{
    m_pValue->append(value);
}

Json& Json::operator[](const std::string& key)
{
    return (*m_pValue)[key];
}

Json& Json::operator[](size_t index)
{
    return (*m_pValue)[index];
}
