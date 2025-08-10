#ifndef _JSONPARSER_H_
#define _JSONPARSER_H_
#include <string>
#include "Json.h"
#include "JsonBase.h"

class JsonParser
{
private:
    const std::string m_str;
    size_t m_pos;
    void skipWhiteSpace();
    char getNextChar();
    char peekNextChar();
    void except(char except);
    Json parseObject();
    Json parseKeyboard(const std::string& key);
    std::string parseString();
    Json parseArray();
    Json parseNumber(); 
public:
    JsonParser(const std::string& str);
    Json parseValue();

};

#endif
