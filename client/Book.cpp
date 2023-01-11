#include <sstream>
#include <utility>
#include <QStringList>

#include "Book.h"
#include "Error.h"

Book::Book(int id,
           int authorId,
           int year,
           float rating,
           QString title,
           QString ISBN,
           const QStringList &genres,
           const QStringList &subgenres)
        : m_Id(id),
          m_AuthorId(authorId),
          m_Year(year),
          m_Rating(rating),
          m_Title(title),
          m_ISBN(ISBN),
          m_Genres(genres),
          m_Subgenres(subgenres) {}

Book::Book(int id,
           int authorId,
           int year,
           float rating,
           QString title,
           QString ISBN,
           const QString &genres,
           const QString &subgenres)
        : m_Id(id),
          m_AuthorId(authorId),
          m_Year(year),
          m_Rating(rating),
          m_Title(title),
          m_ISBN(ISBN),
          m_Genres(genres.split(',')),
          m_Subgenres(subgenres.split(',')) {}

Book::Book(QString fromQString) {
    QStringList x = fromQString.split(':');
    if(x.size() >= 8) {
        m_Id = x[0].toInt();
        m_AuthorId = x[1].toInt();
        m_Year = x[2].toInt();
        m_Rating = x[3].toFloat();
        m_Title = x[4];
        m_ISBN = x[5];
        m_Genres = x[6].split(',');
        m_Subgenres = x[7].split(',');
    }
    else {
        m_Id = -1;
    }
}

string Book::ToString() const {
    char output[2048];
    snprintf(output, 2048, "%d:%d:%d:%f:%s:%s:%s:%s",
             m_Id,
             m_AuthorId,
             m_Year,
             m_Rating,
             m_Title.toStdString().c_str(),
             m_ISBN.toStdString().c_str(),
             GetGenresAsString().toStdString().c_str(),
             GetSubgenresAsString().toStdString().c_str());
    return output;
}
