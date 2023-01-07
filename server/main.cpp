#include "Server.h"

int main() {
    auto server = Server(8083, 10);
    server.Start();

    return 0;
}

//#include <sqlite3.h>
//#include <iostream>
//
//int main() {
//    sqlite3* db;
//    int rc = sqlite3_open("test.db", &db);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
//        return 1;
//    }
//
//    char* sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT)";
//    char* errmsg;
//    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Error creating table: " << errmsg << std::endl;
//        sqlite3_free(errmsg);
//        return 1;
//    }
//
//    sql = "INSERT INTO test (name) VALUES ('Hello, world!')";
//    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Error inserting data: " << errmsg << std::endl;
//        sqlite3_free(errmsg);
//        return 1;
//    }
//
//    sqlite3_close(db);
//    return 0;
//}