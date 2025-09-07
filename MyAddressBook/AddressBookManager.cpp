#include "AddressBookManager.h"
#include "SqliteWrapper.h"
//#include "table.h"

AddressBookManager::AddressBookManager()
{
    m_strDBName = "contacts.DB";
}

bool AddressBookManager::CreateTable()
{
								//CMAutoLock<CMMutex> lock(m_hSqlite3Mutex);
				    SqliteWrapper db;
								if (db.open_db(m_strDBName) != SQLITE_OK)
								{
												return false;
								}
								db.open_query(ADDRESS_BOOK);
								db.close_query();
								db.close_db();
								return true;
}


int AddressBookManager::GetData(const string& strSQL, std::vector<ContactInfo>& vContact)
{
				//CMAutoLock<CMMutex> lock(m_hSqlite3Mutex);
				vContact.clear();
				SqliteWrapper db;
				if (db.open_db(m_strDBName) != SQLITE_OK)
				{
								printf("fail to open db:%s\n", m_strDBName.c_str());
								return SQL_OPEN_DB_ERROR;
				}

				bool bQuery = db.open_query(strSQL);
				if (!bQuery)
				{
								db.close_query();
								db.close_db();
								return SQL_OPERATE_ERROR;
				}

				do
				{
								char szName[48];
								char szAddress[50];
								char szEmail[40];
								char szTelephone[90];
								char szCompany[100];

		
								ContactInfo temp;

								db.get_field("name", szName);
								temp.strName.append(szName);
								db.get_field("address", szAddress);
								temp.strAddress.append(szAddress);
								db.get_field("email", szEmail);
								temp.strEmail.append(szEmail);
								db.get_field("telephone", szTelephone);
								temp.strTelephone.append(szTelephone);
								db.get_field("company", szCompany);
								temp.strCompany.append(szCompany);
			

								db.get_field("id", &temp.nID);
								db.get_field("created_time", &temp.nCreated_time);
								db.get_field("relationship", &temp.nRelationship);
						
							
								vContact.push_back(temp);
				} while (db.move_next());

				db.close_query();
				db.close_db();
				return SQL_SUCCESS;
}


int AddressBookManager::UpdateData(const std::string& strSQL)
{
				std::vector<std::string> vSQL;
				vSQL.push_back(strSQL);
				return UpdateData(vSQL);
}


int AddressBookManager::UpdateData(const std::vector<std::string>& vSQL)
{
				if (0 == vSQL.size())
				{
								return SQL_INVALID_INPUT;
				}
				SqliteWrapper  db;
				if (db.open_db(m_strDBName) != SQLITE_OK)
				{
								printf("fail to open db:%s\n", m_strDBName.c_str());
								return SQL_OPEN_DB_ERROR;
				}

				bool bDel = db.sql_update(vSQL);
				if (!bDel)
				{
								db.close_db();
								printf("fail to update:number %d\n", vSQL.size());
								return SQL_OPERATE_ERROR;
				}
				db.close_db();
				return SQL_SUCCESS;
}

int AddressBookManager::DeleteData(const std::string& strSQL)
{
				std::vector<std::string> vSQL;
				vSQL.push_back(strSQL);
				return DeleteData(vSQL);
}

int AddressBookManager::DeleteData(const std::vector<std::string>& vSQL)
{
				if (0 == vSQL.size())
				{
								return SQL_INVALID_INPUT;
				}

				SqliteWrapper  db;
				if (db.open_db(m_strDBName) != SQLITE_OK)
				{
								printf("fail to open db:%s\n", m_strDBName.c_str());
								return SQL_OPEN_DB_ERROR;
				}
				bool bDel = db.sql_delete(vSQL);
				if (!bDel)
				{
								db.close_db();
								printf("fail to delete:number %d\n", vSQL.size());
								return SQL_OPERATE_ERROR;
				}
				db.close_db();
				return SQL_SUCCESS;
}

int AddressBookManager::InsertData(const std::string& strSQL)
{
				std::vector<std::string> vSQL;
				vSQL.push_back(strSQL);
				return InsertData(vSQL);
}
int AddressBookManager::InsertData(const std::vector<std::string>& vSQL)
{
				if (0 == vSQL.size())
				{
								return SQL_INVALID_INPUT;
				}
				SqliteWrapper  db;
				if (db.open_db(m_strDBName) != SQLITE_OK)
				{
								printf("fail to open db:%s\n", m_strDBName.c_str());
								return SQL_OPEN_DB_ERROR;
				}

				bool bInsert = db.sql_insert(vSQL);
				if (!bInsert)
				{
								db.close_db();
								printf("fail to insert:number %d\n", vSQL.size());
								return SQL_OPERATE_ERROR;
				}

				db.close_db();
				return SQL_SUCCESS;
}

int AddressBookManager::LookupData(const std::string& strSQL)
{
				SqliteWrapper  db;
				if (db.open_db(m_strDBName) != SQLITE_OK)
				{
								printf("fail to open db:%s\n", m_strDBName.c_str());
								return SQL_OPEN_DB_ERROR;
				}

				bool bQuery = db.open_query(strSQL);
				if (!bQuery)
				{
								db.close_query();
								db.close_db();
								return SQL_OPERATE_ERROR;
				}

				int nData = 0;
				db.get_field(0, &nData);
				int nCount = nData;
				db.close_query();
				db.close_db();
				return nCount;
}