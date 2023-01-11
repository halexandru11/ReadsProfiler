#include "bookwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

BookWidget::BookWidget(QWidget *parent, Book* book)
    : QWidget{parent}, m_Book(book)
{
    QPixmap pixmap = QPixmap(":/icon/images/book.jpg");

    QLabel *label1 = new QLabel();
    QLabel *label2 = new QLabel(book->GetTitle());
    QLabel *label3 = new QLabel(QString("Rating: %1/5").arg(book->GetRating()));
    label1->setPixmap(pixmap);
    label1->setScaledContents(true);
    label2->setStyleSheet("color: black");
    label3->setStyleSheet("color: black");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);

    setMinimumSize(180, 260);
    setMaximumSize(180, 260);
    setLayout(layout);
}
