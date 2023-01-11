#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Book {
public:
    Book(int id,
         int authorId,
         int year,
         float rating,
         string title,
         string ISBN,
         const vector<string> &genres,
         const vector<string> &subgenres);

    Book(int id,
         int authorId,
         int year,
         float rating,
         string title,
         string ISBN,
         const string &genres,
         const string &subgenres);

    [[nodiscard]] string ToString() const;

private:
    int m_Id, m_AuthorId, m_Year;
    float m_Rating;
    string m_Title, m_ISBN;
    vector<string> m_Genres, m_Subgenres;

private:
    static vector<string> SplitString(std::stringstream &&str);

    [[nodiscard]] string GenresToString() const;

    [[nodiscard]] string SubgenresToString() const;
};