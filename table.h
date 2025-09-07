#ifndef _TABLE_H_
#define _TABLE_H

#include <string>
using namespace std;

const std::string ADDRESS_BOOK = " create table if not exists contacts("
"id INTEGER primary key autoincrement,"
"name TEXT(50) not NULL,"
"address TEXT,"
"email TEXT,"
"telephone TEXT,"
"company TEXT,"
"created_time INTEGER not NULL,"
"relationship INTEGER"
")";

struct ContactInfo
{
				std::string strName;
				std::string strAddress;
				std::string strEmail;
				std::string strTelephone;
				std::string strCompany;
				int nID;
				int nCreated_time;
				int nRelationship;


};

#endif


