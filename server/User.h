#pragma once

#include <string>

using std::string;

class User {
public:
    explicit User(int id, const string &username, const string &booksRead);

    [[nodiscard]] int GetId() const { return m_Id; }

    [[nodiscard]] string GetUsername() const { return m_Username; }

    [[nodiscard]] string GetBooksRead() const { return m_BooksRead; }

    [[nodiscard]] string ToString() const;

private:
    int m_Id;
    string m_Username, m_BooksRead;
};
