#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>

#include "Book.h"

class BookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookWidget(QWidget *parent = nullptr, Book* book = nullptr);

    Book* GetBook() const { return m_Book; }

private:
    Book* m_Book;
signals:

};

#endif // BOOKWIDGET_H
