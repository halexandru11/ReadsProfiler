#include <sstream>
#include <utility>

#include "Book.h"

Book::Book(int id,
           int authorId,
           int year,
           float rating,
           string title,
           string ISBN,
           const vector<string> &genres,
           const vector<string> &subgenres)
        : m_Id(id),
          m_AuthorId(authorId),
          m_Year(year),
          m_Rating(rating),
          m_Title(std::move(title)),
          m_ISBN(std::move(ISBN)),
          m_Genres(genres),
          m_Subgenres(subgenres) {}

Book::Book(int id,
           int authorId,
           int year,
           float rating,
           string title,
           string ISBN,
           const string &genres,
           const string &subgenres)
        : m_Id(id),
          m_AuthorId(authorId),
          m_Year(year),
          m_Rating(rating),
          m_Title(std::move(title)),
          m_ISBN(std::move(ISBN)) {
    m_Genres = SplitString(std::stringstream(genres));
    m_Subgenres = SplitString(std::stringstream(subgenres));
}

string Book::ToString() const {
    char output[1024];
    snprintf(output, 1024, "%d:%d:%d:%f:%s:%s:%s:%s",
             m_Id,
             m_AuthorId,
             m_Year,
             m_Rating,
             m_Title.c_str(),
             m_ISBN.c_str(),
             GenresToString().c_str(),
             SubgenresToString().c_str());
    return output;
}

vector<string> Book::SplitString(std::stringstream &&str) {
    vector<string> output;
    string token;
    while (std::getline(str, token, ',')) {
        output.push_back(token);
    }
    return output;
}

string Book::GenresToString() const {
    string output;
    for (const string &genre: m_Genres) {
        output += genre;
        output += ',';
    }
    return output.substr(0, output.size() - 1);
}

string Book::SubgenresToString() const {
    string output;
    for (const string &subgenre: m_Subgenres) {
        output += subgenre;
        output += ',';
    }
    return output.substr(0, output.size() - 1);
}
