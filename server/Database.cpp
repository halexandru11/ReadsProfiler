#include "Database.h"
#include "Error.h"
#include <iostream>

sqlite3 *Database::s_Db = nullptr;

void Database::Open() {
    int status = sqlite3_open("../ReadsProfiler.db", &s_Db);
    if (status != SQLITE_OK) {
        Error::Print("Could not open database");
    }
}

void Database::Close() {
    sqlite3_close(s_Db);
}


User Database::GetUserIdByUsernameAndPassword(const string &username, const string &password) {
    string query = "SELECT id, username, books_read FROM users WHERE TRIM(USERNAME)=? AND TRIM(PASSWORD)=?";

    sqlite3_stmt *stmt;
    int status = sqlite3_prepare_v2(s_Db, query.c_str(), -1, &stmt, nullptr);
    if (status != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return User(-1, "", "");
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string booksRead = (const char *) sqlite3_column_text(stmt, 2);
        auto user = User(id, username, booksRead);
        sqlite3_finalize(stmt);
        return user;
    }
    sqlite3_finalize(stmt);
    return User(-1, "", "");
}

void Database::ExecuteQuery(const string &query) {
    try {
        char *errorMesssage;
        int status = sqlite3_exec(s_Db, query.c_str(), nullptr, nullptr, &errorMesssage);
        if (status != SQLITE_OK) {
            Error::Print(errorMesssage);
            sqlite3_free(errorMesssage);
        }
    }
    catch (const std::exception &e) {
        Error::Print(e.what());
    }
}

vector<Book> Database::GetAllBooks() {
    string query = "SELECT * FROM books";

    sqlite3_stmt *stmt;
    int status = sqlite3_prepare_v2(s_Db, query.c_str(), -1, &stmt, nullptr);
    if (status != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return {};
    }

    vector<Book> books;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string title = (const char *) sqlite3_column_text(stmt, 1);
        int authorId = sqlite3_column_int(stmt, 2);
        int year = sqlite3_column_int(stmt, 3);
        string ISBN = (const char *) sqlite3_column_text(stmt, 4);
        auto rating = (float) sqlite3_column_double(stmt, 5);
        string gendres = (const char *) sqlite3_column_text(stmt, 6);
        string subgendres = (const char *) sqlite3_column_text(stmt, 7);
        Book book = Book(id, authorId, year, rating, title, ISBN, gendres, subgendres);
        books.push_back(book);
    }
    sqlite3_finalize(stmt);
    return books;
}


vector<Book> Database::GetBooksWithGenre(string genre) {
    string query = "SELECT * FROM books WHERE TRIM(GENDERS) LIKE ?";

    sqlite3_stmt *stmt;
    int status = sqlite3_prepare_v2(s_Db, query.c_str(), -1, &stmt, nullptr);
    if (status != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return {};
    }

    genre = "%" + genre + "%";
    sqlite3_bind_text(stmt, 1, genre.c_str(), -1, SQLITE_TRANSIENT);

    vector<Book> books;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string title = (const char *) sqlite3_column_text(stmt, 1);
        int authorId = sqlite3_column_int(stmt, 2);
        int year = sqlite3_column_int(stmt, 3);
        string ISBN = (const char *) sqlite3_column_text(stmt, 4);
        auto rating = (float) sqlite3_column_double(stmt, 5);
        string gendres = (const char *) sqlite3_column_text(stmt, 6);
        string subgendres = (const char *) sqlite3_column_text(stmt, 7);
        Book book = Book(id, authorId, year, rating, title, ISBN, gendres, subgendres);
        books.push_back(book);
    }
    sqlite3_finalize(stmt);
    return books;
}

string Database::GetBookContent(int bookId) {
    string query = "SELECT content FROM books_content";

    sqlite3_stmt *stmt;
    int status = sqlite3_prepare_v2(s_Db, query.c_str(), -1, &stmt, nullptr);
    if (status != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return {};
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        string content = (const char *) sqlite3_column_text(stmt, 0);
        std::cout << "This is the contents: ";
        std::cout << content << std::endl;
        sqlite3_finalize(stmt);
        return content;
    }
    std::cout << "There is no content" << std::endl;
    sqlite3_finalize(stmt);
    return "";
}
