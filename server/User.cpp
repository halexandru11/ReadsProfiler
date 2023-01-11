#include "User.h"

#include <iostream>

User::User(int id, const string &username, const string &booksRead)
        : m_Id(id), m_Username(username), m_BooksRead(booksRead) {
    std::cout << "I am here\n";
    std::cout.flush();
}

string User::ToString() const {
    return std::to_string(m_Id) + ":" + m_Username + ":" + m_BooksRead;
}
