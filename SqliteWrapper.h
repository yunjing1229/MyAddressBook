#ifndef SQLITE_WRAPPER_H_
#define SQLITE_WRAPPER_H

#include <string>
#include <vector>
#include "sqlite3.h"


using namespace std;

class SqliteWrapper
{
public:
				SqliteWrapper();
				~SqliteWrapper();
public:
				int  open_db(const std::string& strDBName);
				bool close_db();
				bool open_query(const std::string& strSQL);
				void close_query();
				bool get_field(int index, void* field_value);
				bool get_field(const std::string& strFieldName, void* field_value);
				bool move_next();
				bool sql_update(const std::vector<std::string>& vSQL);
				bool sql_delete(const std::vector<std::string>& vSQL);
				bool sql_insert(const std::vector<std::string>& vSQL);

private:
				sqlite3* m_DB;
				sqlite3_stmt* m_pStmt;
				int m_nColCount;
};

#endif
;

