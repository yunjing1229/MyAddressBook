#ifndef _JSONBASE_H_
#define _JSONBASE_H_
#include <stdexcept>
#include "Json.h"
#include <string>

class JsonBase
{
public:
				virtual ~JsonBase() {} 
				virtual Json::Type  type() const = 0;
				virtual JsonBase* clone() const = 0;
				virtual std::string toString() const = 0;
				virtual void set(const std::string& key, const Json& value) { }
				virtual void append(const Json& value) { }
				virtual Json& operator[](const std::string& key) { throw std::runtime_error("unexcept end of str"); }//{ throw std::runtime_error("unexcept end of str"); }
				virtual Json& operator[](size_t index) { throw std::runtime_error("unexcept end of str"); }
				virtual const Json& operator[](size_t index) const{ throw std::runtime_error("unexcept end of str"); }
	 
};



#endif

