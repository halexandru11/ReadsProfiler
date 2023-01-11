#pragma once

#include <QString>
#include <QStringList>
#include <string>
#include <vector>
#include <QString>

using std::string;
using std::vector;

class Book {
public:
    Book(QString fromQString);

    Book(int id,
         int authorId,
         int year,
         float rating,
         QString title,
         QString ISBN,
         const QStringList &genres,
         const QStringList &subgenres);

    Book(int id,
         int authorId,
         int year,
         float rating,
         QString title,
         QString ISBN,
         const QString &genres,
         const QString &subgenres);

    int GetId() const { return m_Id; }

    int GetAuthorId() const { return m_AuthorId; }

    int GetYear() const { return m_Year; }

    float GetRating() const { return m_Rating; }

    QString GetTitle() const { return m_Title; }

    QString GetISBN() const { return m_ISBN; }

    QStringList GetGenres() const { return m_Genres; }

    QStringList GetSubgenres() const { return m_Subgenres; }

    QString GetGenresAsString() const { return m_Genres.join(','); }

    QString GetSubgenresAsString() const { return m_Subgenres.join(','); }

    string ToString() const;

//    bool operator< (const Book &other) const {
//        return m_Rating < other.m_Rating;
//    }

//    QString ToQString() const;

private:
    int m_Id, m_AuthorId, m_Year;
    float m_Rating;
    QString m_Title, m_ISBN;
    QStringList m_Genres, m_Subgenres;
};
