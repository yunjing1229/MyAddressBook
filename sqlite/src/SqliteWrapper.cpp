#include "SqliteWrapper.h"
#include "table.h"


SqliteWrapper::SqliteWrapper()
{
    m_DB = NULL;
    m_nColCount = 0;
}

SqliteWrapper::~SqliteWrapper()
{
    if (m_DB)
    {
        close_db();
    }
}

int  SqliteWrapper::open_db(const std::string& strDBName)
{
    int nResult = sqlite3_open(strDBName.c_str(), &m_DB);
    if (nResult)
    {
        sqlite3_close(m_DB);
    }
    return nResult;
}

bool SqliteWrapper::close_db()
{
    if (sqlite3_close(m_DB) == SQLITE_OK)
    {
        m_DB = NULL;
        return true;
    }
    return false;
}


bool SqliteWrapper::open_query(const std::string& strSQL)
{
    int nResult = sqlite3_prepare_v2(m_DB, strSQL.c_str(), -1, &m_pStmt, NULL);
    if (nResult != SQLITE_OK)
    {
        sqlite3_finalize(m_pStmt);
        return false;
    }

    nResult = sqlite3_step(m_pStmt);
    if (nResult == SQLITE_ROW)
    {
        m_nColCount = sqlite3_column_count(m_pStmt);
        return true;
    }
    else if (nResult == SQLITE_DONE)
    {
        return true;
    }

    return false;
}

void SqliteWrapper::close_query()
{
    sqlite3_finalize(m_pStmt);
}

bool SqliteWrapper::get_field(int index, void* field_value)
{
    switch (sqlite3_column_type(m_pStmt, index))
    {
    case SQLITE_INTEGER:
        *((int*)field_value);
        break;
    case SQLITE_FLOAT:
        *((double*)field_value);
        break;
    case SQLITE_TEXT:
        *((char*)field_value);
        break;
    case SQLITE_BLOB:
        break;
    case SQLITE_NULL:
        return false;
    default:
        return false;
    }
    return true;
   
}

bool SqliteWrapper::get_field(const std::string& strFieldName, void* field_value)
{
    for (int i = 0; i < m_nColCount; i++)
    {
        string strName = sqlite3_column_name(m_pStmt, i);
        if (strName == strFieldName)
        {
            switch (sqlite3_column_type(m_pStmt, i))
            {
            case SQLITE_INTEGER:
                *((int*)field_value) = sqlite3_column_int(m_pStmt, i);
                break;

            case SQLITE_TEXT:
                sprintf(((char*)field_value), "%s", sqlite3_column_text(m_pStmt, i));
                break;

            case SQLITE_BLOB:
                break;
            case SQLITE_FLOAT:
                *((double*)field_value) = sqlite3_column_double(m_pStmt, i);
                break;

            case SQLITE_NULL:
                return  false;

            default:
                return  false;
            }

           break;
        }
    }
    return true;
}

bool SqliteWrapper::move_next()
{
    if (sqlite3_step(m_pStmt) == SQLITE_ROW)
    {
        return true;
    }
    return false;
}


bool SqliteWrapper::sql_update(const std::vector<std::string>& vSQL)
{
    char* errMsg = 0;

    int nResult = sqlite3_exec(m_DB, "BEGIN", 0, 0, &errMsg);
    int nSize = vSQL.size();
    for (int i = 0; i < nSize; i++)
    {
        nResult = sqlite3_exec(m_DB, vSQL[i].c_str(), 0, 0, &errMsg);
        if (nResult != SQLITE_OK)
        {
            return false;
        }
    }
    nResult = sqlite3_exec(m_DB, "COMMIT", 0, 0, &errMsg);
    return true;
}

bool SqliteWrapper::sql_delete(const std::vector<std::string>& vSQL)
{
    char* errMsg = 0;

    int nResult = sqlite3_exec(m_DB, "BEGIN", 0, 0, &errMsg);
    int nSize = vSQL.size();
    for (int i = 0; i < nSize; i++)
    {
         nResult = sqlite3_exec(m_DB, vSQL[i].c_str(), 0, 0, &errMsg);
        if (nResult != SQLITE_OK)
        {
            return false;
        }
    }
    nResult = sqlite3_exec(m_DB, "COMMIT", 0, 0, &errMsg);
    return true;
}

bool SqliteWrapper::sql_insert(const std::vector<std::string>& vSQL)
{
    char* errMsg = 0;

    int nResult = sqlite3_exec(m_DB, "BEGIN", 0, 0, &errMsg);
    int nSize = vSQL.size();
    for (int i = 0; i < nSize; i++)
    {
        nResult = sqlite3_exec(m_DB, vSQL[i].c_str(), 0, 0, &errMsg);
        if (nResult != SQLITE_OK)
        {
            return false;
        }
    }
    nResult = sqlite3_exec(m_DB, "COMMIT", 0, 0, &errMsg);
    return true;
}