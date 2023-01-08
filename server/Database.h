#pragma once

#include <sqlite3.h>
#include <string>

using std::string;

class Database {
public:
    Database() = delete;

    static void Open();

    static void Close();

    static void CreateTablesIfNotExist();

    static int GetUserIdByUsernameAndPassword(const string& username, const string& password);

private:
    static sqlite3* s_Db;

private:
    static void ExecuteQuery(const string& query);

    static sqlite3_stmt* ExecuteSelectQuery(const string& query);

    static void CreateUsersTable();

    static void CreateBooksTable();

    static void CreateAuthorsTable();
};