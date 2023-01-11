#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>

#include "Book.h"
#include "User.h"

using std::string;
using std::vector;

class Database {
public:
    Database() = delete;

    static void Open();

    static void Close();

    static User GetUserIdByUsernameAndPassword(const string &username, const string &password);

    static vector<Book> GetAllBooks();

    static vector<Book> GetBooksWithGenre(string genre);

    static string GetBookContent(int bookId);

private:
    static sqlite3 *s_Db;

private:
    static void ExecuteQuery(const string &query);
};