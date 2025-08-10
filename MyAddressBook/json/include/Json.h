#ifndef _JSON_H_
#define _JSON_H_
#include <string>

class JsonBase;

class Json
{
public:
	enum Type
	{
		JSOM_NULL,
		JSON_BOOL,
		JSON_STRING,
		JSON_NUMBER,
		JSON_ARRAY,
		JSON_OBJECT
	};

	static Json Object();
	static Json Array();
	static Json Parse(const std::string& str);
	Json();
	explicit Json(const char* str);
	explicit Json(double fValue);
	explicit Json(int nValue);
	explicit Json(const std::string& str);
	explicit Json(bool bValue);
	explicit Json(JsonBase* s);
	std::string toString() const;
	Json& operator[](const std::string& key);
	Json& operator[](size_t index);
	void set(const std::string& key, const Json& value);
	void append(const Json& value);
private:
				JsonBase* m_pValue;
};

#endif


