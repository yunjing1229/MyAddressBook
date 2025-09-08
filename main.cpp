#include "Json.h"
#include "JsonParser.h"
#include <iostream>
#include <vector>
#include<string>
#include <sqlite3.h>
//#include "table.h"
#include "SqliteWrapper.h"
#include <cstdio>
#include "AddressBookManager.h"
using namespace std;

int main()
{
    AddressBookManager test;
    bool bCreate = true;
    std::string filename = "contacts.DB";
    FILE* file = fopen(filename.c_str(), "r");
 
    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        if (fileSize > 0)
        {
            bCreate = false;
        }
    }
  
    if (bCreate)
    {
        test.CreateTable();
        test.UpdateData("INSERT INTO contacts (name, address, email, telephone, company, created_time, relationship)"
            " values(\"wang\", \"东方路\", \"wang@163.com\", \"14355\", \"\", 1, 2);");
        test.UpdateData("INSERT INTO contacts (name, address, email, telephone, company, created_time, relationship)"
            " values(\"li\", \"南京路\", \"li@163.com\", \"12875\", \"\", 1, 2);");
        test.UpdateData("INSERT INTO contacts (name, address, email, telephone, company, created_time, relationship)"
            " values(\"liu\", \"锦绣路\", \"liu@163.com\", \"19865\", \"\", 1, 2);");
    }
    std::vector<ContactInfo> contacts;
    test.GetData("SELECT * FROM contacts", contacts);
    
    Json Addressbook = Json::Object();
    Json contact = Json::Array();
    
    for (ContactInfo text : contacts)
    {
        Json ID = Json::Object();
        ID.set("ID", Json(text.nID));
        ID.set("Name", Json(text.strName));
        ID.set("Address", Json(text.strAddress));
        ID.set("Email", Json(text.strEmail));
        contact.append(ID);

    }
    
    Addressbook.set("contact", contact);
    cout << Addressbook.toString();

				return 0;

}