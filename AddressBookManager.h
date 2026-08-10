#ifndef ADDRESS_BOOK_MANAGER_H_
#define ADDRESS_BOOK_MANAGER_H_
#include <string>
#include <vector>
#include <map>
//#include "SqliteWrapper.h"
#include "table.h"
#include <sqlite3.h>

using namespace std;

enum Sql_ErrorCode
{
				SQL_SUCCESS = 0,
				SQL_OPEN_DB_ERROR = -1,
				SQL_OPERATE_ERROR = -2,
				SQL_INVALID_INPUT = -3
};


class AddressBookManager
{
public:
				AddressBookManager();
				bool CreateTable();
				int GetData(const std::string& strSQL, std::vector<ContactInfo>& vContactInfo);
				int UpdateData(const std::string& strSQL);
				int UpdateData(const std::vector<std::string>& vSQL);
				int DeleteData(const std::string& strSQL);
				int DeleteData(const std::vector<std::string>& vSQL);
				int InsertData(const std::string& strSQL);
				int InsertData(const std::vector<std::string>& vSQL);
				int LookupData(const std::string& strSQL);
private:
				//CMMutex m_hSqlite3Mutex;
				std::string m_strDBName;
};

#endif

