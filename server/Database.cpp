#include "Database.h"
#include "Error.h"

sqlite3* Database::s_Db = nullptr;

void Database::Open() {
    int status = sqlite3_open("test.db", &s_Db);
    if(status != SQLITE_OK) {
        Error::Print("Could not open database");
    }
}

void Database::Close() {
    sqlite3_close(s_Db);
}

void Database::CreateTablesIfNotExist() {
    CreateUsersTable();
    CreateBooksTable();
    CreateAuthorsTable();
}

void Database::CreateUsersTable() {
    string query = "CREATE TABLE IF NOT EXISTS USERS("
                   "ID          INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "USERNAME    TEXT NOT NULL, "
                   "PASSWORD    TEXT NOT NULL);";

    ExecuteQuery(query);
}

void Database::CreateBooksTable() {
    string query = "CREATE TABLE IF NOT EXISTS BOOKS("
                   "ID          INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "TITLE       TEXT NOT NULL, "
                   "AUTHOR_ID   INTEGER NOT NULL, "
                   "ISBN        TEXT NOT NULL, "
                   "RATING      NUMBER NOT NULL, "
                   "GENDERS     TEXT NOT NULL, "
                   "SUBGENDERS  TEXT NOT NULL);";

    ExecuteQuery(query);
}

void Database::CreateAuthorsTable() {
    string query = "CREATE TABLE IF NOT EXISTS AUTHORS("
                   "ID          INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "NAME        TEXT NOT NULL, "
                   "GENDERS     INTEGER NOT NULL, "
                   "SUBGENDERS  TEXT NOT NULL);";

    ExecuteQuery(query);
}

int Database::GetUserIdByUsernameAndPassword(const string &username, const string &password) {
    string query = "SELECT id FROM users "
                   "WHERE username=\"" + username + "\" AND password=\"" + password + "\";";
    sqlite3_stmt* stmt = ExecuteSelectQuery(query);
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        return sqlite3_column_int(stmt, 0);
    }
    return -1;
}

void Database::ExecuteQuery(const string& query) {
    try {
        char *errorMesssage;
        int status = sqlite3_exec(s_Db, query.c_str(), nullptr, nullptr, &errorMesssage);
        if (status != SQLITE_OK) {
            Error::Print(errorMesssage);
            sqlite3_free(errorMesssage);
        }
    }
    catch (const std::exception& e) {
        Error::Print(e.what());
    }
}

sqlite3_stmt* Database::ExecuteSelectQuery(const string &query) {
    sqlite3_stmt* stmt;
    int status = sqlite3_prepare_v2(s_Db, query.c_str(), -1, &stmt, nullptr);
    if(status != SQLITE_OK) {
        Error::Print(sqlite3_errmsg(s_Db));
        return nullptr;
    }
    return stmt;
}
