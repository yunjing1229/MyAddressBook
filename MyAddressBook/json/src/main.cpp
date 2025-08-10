#include "Json.h"
#include "JsonParser.h"
#include <iostream>
using namespace std;


int main()
{
				Json p = Json::Object();
				//p.set("name", Json("Ruihan"));
			 //p.set("age", Json(124));
				//p.set("isStudent", Json(true));
				Json hobbies = Json::Array();
			 hobbies.append(Json("football"));
				hobbies.append(Json("violin"));
			 p.set("hobbies", hobbies);
				//Json address = Json::Object();
				//address.set("street", Json("123 Main St"));
				//p.set("address", address);
				cout << p.toString();
				Json parse = Json::Parse(p.toString());
				cout << endl  << parse["hobbies"][1].toString();

				return 0;

}