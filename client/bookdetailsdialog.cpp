#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDialogButtonBox>

#include "bookdetailsdialog.h"
#include "mainwindow.h"

BookDetailsDialog::BookDetailsDialog(Book* book) : m_Book(book)
{
    setWindowTitle(book->GetTitle());
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QPixmap pixmap = QPixmap(":/icon/images/book.jpg");

    QLabel *label1 = new QLabel();
    QLabel *label2 = new QLabel(book->GetTitle());
    QLabel *label3 = new QLabel(QString("Aparition year: %1").arg(book->GetYear()));
    QLabel *label4 = new QLabel(QString("Rating: %1/5").arg(book->GetRating()));
    QLabel *label5 = new QLabel(QString("ISBN: %1").arg(book->GetISBN()));
    QLabel *label6 = new QLabel(QString("Genres: %1").arg(book->GetGenresAsString()));
    QLabel *label7 = new QLabel(QString("Subgenres: %1").arg(book->GetSubgenresAsString()));
    QLabel *label8 = new QLabel("\n\nWant to download the book? Press OK.");
    label1->setPixmap(pixmap);
    label1->setScaledContents(true);
    label8->setStyleSheet("color: yellow;");
    label8->hide();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);
    layout->addWidget(label4);
    layout->addWidget(label5);
    layout->addWidget(label6);
    layout->addWidget(label7);
    layout->addWidget(label8);
    layout->addWidget(buttonBox);

    setMinimumSize(400, 600);
    setMaximumSize(400, 600);
    setLayout(layout);

    exec();
}

void BookDetailsDialog::accept() {
    MainWindow::client.DownloadBook(m_Book->GetId());
    QDialog::accept();
}
