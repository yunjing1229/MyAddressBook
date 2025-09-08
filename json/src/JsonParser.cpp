#include "JsonParser.h"
#include <stdexcept>
using namespace std;

void JsonParser::skipWhiteSpace()
{
    if (m_pos <= m_str.size() && isspace(m_str[m_pos]))
    {
        ++m_pos;
    }
}

char JsonParser::getNextChar()
{
    skipWhiteSpace();
    if (m_pos > m_str.size())
    {
        throw std::runtime_error("unexcept end of str");
    }
    return m_str[m_pos++];
}


char JsonParser::peekNextChar()
{
    skipWhiteSpace();
    if (m_pos > m_str.size())
    {
        throw std::runtime_error("unexcept end of str");
    }
    return m_str[m_pos];
}

void JsonParser::except(char excepted)
{
    char c = getNextChar();
    if (c != excepted)
    {
        throw runtime_error("unexcept char");
    }
}

Json JsonParser::parseObject()
{
    Json result = Json::Object();
    m_pos--;
    except('{');
    if (peekNextChar() == '}')
    {
        getNextChar();
        return result;
    }
    while (true)
    {
        std::string key = parseString();
        except(':');
        Json value = parseValue();
        result.set(key, value);

        char c = getNextChar();
        if (c == '}')
        {
            return result;
        }
  
        else if (c != ',')
        {
            throw runtime_error("unexcept end of Json object");
        }
    }
    return result;
}

std::string JsonParser::parseString()
{
    except('"');
    std::string result;
    while (m_pos < m_str.size())
    {
        char c = m_str[m_pos++];
        if ('"' == c)
        {
            return result;
        }
        result += c;
    }
    throw runtime_error("invalid string");
}

Json JsonParser::parseKeyboard(const std::string& key)
{
    m_pos += key.size() - 1;
    if (key == "true")
    {
        return Json(true);
    }
    if (key == "false")
    {
        return Json(false);
    }
}

Json JsonParser::parseNumber()
{
    size_t pos = m_pos - 1;
    bool isDouble = false;

    if (m_str[pos] == '-')
    {
        ++m_pos;
    }
    while (m_pos < m_str.size())
    {
        char c = m_str[m_pos];
        if (isdigit(c))
        {
            ++m_pos;
        }
        else if (c == '.' || c == 'e' || c == 'E')
        {
            isDouble = true;
            m_pos++;
            if (c == 'e' || c == 'E')
            { 
                if (m_pos < m_str.size() && (m_str[m_pos] == '-' || m_str[m_pos] == '+'))
                {
                    ++m_pos;
                 }
            }
         }
        else
        {
            break;
        }
    }
    std::string numstr = m_str.substr(pos, m_pos - pos);

    if (isDouble)
    {
        char* end;
        double value = strtod(numstr.c_str(), &end);
        if (end != numstr.c_str() + numstr.size())
        {
            throw runtime_error("invslid double");
        }
        return Json(value);
    }
    else
    {
        char* end;
        long value = strtol(numstr.c_str(), &end, 10);
        if (end != numstr.c_str() + numstr.size())
        {
            throw runtime_error("invslid double");
        }
        return Json(static_cast<int>(value));

    }
}

Json JsonParser::parseArray()
{
    Json result = Json::Array();
    m_pos--;
    except('[');

    if (peekNextChar() == ']')
    {
        getNextChar();
        return result;
    }

    while (true)
    {
        result.append(parseValue());

        char c = getNextChar();
        if (']' == c)
        {
            return result;
        }
        else if (c != ',')
        {
            throw runtime_error("invslid array");
        }
    }
}

JsonParser::JsonParser(const std::string& str) : m_str(str), m_pos(0) {}

Json JsonParser::parseValue()
{
    char c = getNextChar();

    switch (c)
    {
    case 'f':
        return parseKeyboard("false");
    case't':
        return parseKeyboard("true");
    case '{':           
        return parseObject();
    case'"':
        m_pos--;
        return Json(parseString());
    case'[':
        return parseArray();
    case'-':
    case'0':
    case'1':
    case'2':
    case'3':
    case'4':
    case'5':
    case'6':
    case'7':
    case'8':
    case'9':
        return parseNumber();
    default:
    {

    }
    }
    
}