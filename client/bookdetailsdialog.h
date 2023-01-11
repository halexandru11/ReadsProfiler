#ifndef BOOKDETAILSDIALOG_H
#define BOOKDETAILSDIALOG_H

#include <QDialog>

#include "Book.h"

class BookDetailsDialog : public QDialog
{
public:
    BookDetailsDialog(Book* book);

    void accept();

private:
    Book* m_Book;
};

#endif // BOOKDETAILSDIALOG_H
