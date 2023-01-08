#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Book {
public:
    Book(int id,
         int authorId,
         double rating,
         string title,
         string ISBN,
         const vector<string> &genres,
         const vector<string> &subgenres);

    Book(int id,
         int authorId,
         double rating,
         string title,
         string ISBN,
         const string &genres,
         const string &subgenres);

    string ToString();

private:
    int m_Id, m_AuthorId;
    double m_Rating;
    string m_Title, m_ISBN;
    vector<string> m_Genres, m_Subgenres;

private:
    static vector<string> SplitString(std::stringstream &&str);

    string GenresToString();

    string SubgenresToString();
};