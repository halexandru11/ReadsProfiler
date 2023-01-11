#include <QHeaderView>
#include <QMessageBox>
#include <QGroupBox>
#include <QCheckBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridview.h"
#include "filterdialogbox.h"
#include "logindialogbox.h"
#include "Error.h"
#include "bookdetailsdialog.h"

Client MainWindow::client = Client("127.0.0.1", 8112);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* logoutBtn = ui->appBar->findChild<QPushButton*>("logoutBtn");
    QPushButton* filterBtn = ui->appBar->findChild<QPushButton*>("filterBtn");
    QPushButton* loginBtn = ui->appBar->findChild<QPushButton*>("loginBtn");
    QLineEdit* searchBar = ui->appBar->findChild<QLineEdit*>("lineEdit");

    if(logoutBtn != nullptr) {
        logoutBtn->setStyleSheet("QPushButton:pressed { background-color: rgb(26, 95, 180); border: none; border-radius: 5; }");
        logoutBtn->hide();
    }
    if(filterBtn != nullptr) {
        filterBtn->setStyleSheet("QPushButton:pressed { background-color: rgb(26, 95, 180); border: none; border-radius: 5; }");
        connect(filterBtn, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    }
    if(loginBtn != nullptr) {
        loginBtn->setStyleSheet("QPushButton:pressed { background-color: rgb(26, 95, 180); border: none; border-radius: 5; }");
        connect(loginBtn, &QPushButton::clicked, this, &MainWindow::handleLoginButtonClick);
    }
    if(searchBar != nullptr) {
        connect(searchBar, &QLineEdit::returnPressed, this, &MainWindow::Search);
    }

    Populate();
}

MainWindow::~MainWindow()
{
    delete table;
    delete ui;
}

void MainWindow::Populate() {
    for(QObject* child : ui->body->children()) {
        QWidget* widget = qobject_cast<QWidget*>(child);
        if (widget) {
            widget->setParent(nullptr);
            widget->deleteLater();
        }
    }

    client.GetAllBooksFromServer();

    QList<QString> prefGen = client.GetUser().GetPreferedGen();
    QList<QString> prefSubgen = client.GetUser().GetPreferedSubgen();

    int rowNum = 2*(prefGen.size() + prefSubgen.size());

    table = new QTableWidget(rowNum + 2, 20, ui->body);
    connect(table, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFrameShape(QFrame::NoFrame);
    table->setFrameShadow(QFrame::Plain);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    table->verticalHeader()->setHidden(true);
    table->horizontalHeader()->setHidden(true);
    table->setShowGrid(false);

    for (int row = 0; row < 2 * prefGen.size(); row++) {
        if(row % 2 == 0) {
            table->setSpan(row, 0, 1, table->columnCount());
            QLabel *label = new QLabel(prefGen[row/2]);
            QFont font = label->font();
            font.setBold(true);
            font.setPointSize(20);
            label->setStyleSheet("color: black;");
            label->setFont(font);

            QVBoxLayout* layout = new QVBoxLayout();
            layout->addWidget(label);
            layout->setContentsMargins(30, 10, 0, 5);

            QWidget* container = new QWidget();
            container->setLayout(layout);

            table->setCellWidget(row, 0, container);
        }
        else {
            QList<Book*> books = client.GetBooksGenre(prefGen[row/2].toStdString());
            Error::PrintWithoutErrno(QString("Size is: %1").arg(books.size()).toStdString());
            for (int col = 0; col < 20 && col < books.size(); col++) {
                BookWidget* book = new BookWidget(nullptr, books[col]);

                QVBoxLayout* layout = new QVBoxLayout();
                layout->addWidget(book);
                layout->setContentsMargins(10, 10, 0, 10);

                QWidget* container = new QWidget();
                container->setLayout(layout);

                table->setCellWidget(row, col, container);
            }

        }
    }

    for (int row = 2 * prefGen.size(), index = 0; row < rowNum; row++) {
        if(row % 2 == 0) {
            table->setSpan(row, 0, 1, table->columnCount());
            QLabel *label = new QLabel(prefSubgen[index]);
            QFont font = label->font();
            font.setBold(true);
            font.setPointSize(20);
            label->setStyleSheet("color: black;");
            label->setFont(font);

            QVBoxLayout* layout = new QVBoxLayout();
            layout->addWidget(label);
            layout->setContentsMargins(30, 10, 0, 5);

            QWidget* container = new QWidget();
            container->setLayout(layout);

            table->setCellWidget(row, 0, container);
        }
        else {
            QList<Book*> books = client.GetBooksSubGenre(prefSubgen[index].toStdString());
            for (int col = 0; col < 20 && col < books.size(); col++) {
                BookWidget* book = new BookWidget(nullptr, books[col]);

                QVBoxLayout* layout = new QVBoxLayout();
                layout->addWidget(book);
                layout->setContentsMargins(10, 10, 0, 10);

                QWidget* container = new QWidget();
                container->setLayout(layout);

                table->setCellWidget(row, col, container);
            }
            ++index;
        }
    }

    {
        Error::PrintWithoutErrno("In Suggestions");
        table->setSpan(rowNum, 0, 1, table->columnCount());
        QLabel *label = new QLabel("Suggestions");
        QFont font = label->font();
        font.setBold(true);
        font.setPointSize(20);
        label->setStyleSheet("color: black;");
        label->setFont(font);

        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(label);
        layout->setContentsMargins(30, 10, 0, 5);

        QWidget* container = new QWidget();
        container->setLayout(layout);

        table->setCellWidget(rowNum, 0, container);

        QList<Book*> books = client.GetBooksSugesstions();
        for (int col = 0; col < 20 && col < books.size(); col++) {
            BookWidget* book = new BookWidget(nullptr, books[col]);

            QVBoxLayout* layout = new QVBoxLayout();
            layout->addWidget(book);
            layout->setContentsMargins(10, 10, 0, 10);

            QWidget* container = new QWidget();
            container->setLayout(layout);

            table->setCellWidget(rowNum+1, col, container);
        }
    }

    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    ui->body->layout()->addWidget(table);
}

void MainWindow::GetBooks(QList<BookWidget*>& books)
{
    books.clear();
    for(int i = 0; i < 10; ++i) {
        BookWidget* book = new BookWidget(ui->scrollArea);
        books.append(book);
    }
}

void MainWindow::onCellClicked(int row, int column)
{
    QWidget* cellContent = qobject_cast<QWidget*>(table->cellWidget(row, column));
    if(cellContent == nullptr) {
        return;
    }
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(cellContent->children()[0]);
    if(layout == nullptr) {
        return;
    }
    BookWidget* book = qobject_cast<BookWidget*>(layout->itemAt(0)->widget());
    if(book == nullptr) {
        return;
    }
    if(client.GetUser().GetId() == -1) {
        LoginDialogBox(this);
    }
    else {
        BookDetailsDialog(book->GetBook());
    }
}

void MainWindow::handleButtonClick() {
    FilterDialogBox(this);
}

void MainWindow::handleLoginButtonClick() {
    LoginDialogBox(this, true);
}

void MainWindow::Search() {
    QLineEdit* searchBar = ui->appBar->findChild<QLineEdit*>("lineEdit");
    if(searchBar == nullptr || (searchBar != nullptr && searchBar->text() == "")) {
        Populate();
        return;
    }
    QList<Book*> boo = client.GetBooksSearch(searchBar->text());
    QList<Book*> books1, books2, books3, books4;
    for(int i = 0; i < 10 && i < boo.size(); ++i) {
        books1.push_back(boo[i]);
    }
    for(int i = 10; i < 20 && i < boo.size(); ++i) {
        books2.push_back(boo[i]);
    }
    for(int i = 20; i < 30 && i < boo.size(); ++i) {
        books3.push_back(boo[i]);
    }
    for(int i = 30; i < 50 && i < boo.size(); ++i) {
        books4.push_back(boo[i]);
    }


    for(QObject* child : ui->body->children()) {
        QWidget* widget = qobject_cast<QWidget*>(child);
        if (widget) {
            widget->setParent(nullptr);
            widget->deleteLater();
        }
    }

    client.GetAllBooksFromServer();

    table = new QTableWidget(4, 20, ui->body);
    connect(table, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFrameShape(QFrame::NoFrame);
    table->setFrameShadow(QFrame::Plain);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    table->verticalHeader()->setHidden(true);
    table->horizontalHeader()->setHidden(true);
    table->setShowGrid(false);


    int row = 0;
    for(const QList<Book*>& books : {books1, books2, books3, books4}) {
        for (int col = 0; col < 20 && col < books.size(); col++) {
            BookWidget* book = new BookWidget(nullptr, books[col]);

            QVBoxLayout* layout = new QVBoxLayout();
            layout->addWidget(book);
            layout->setContentsMargins(10, 10, 0, 10);

            QWidget* container = new QWidget();
            container->setLayout(layout);

            table->setCellWidget(row, col, container);
        }
        ++row;
    }

    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    ui->body->layout()->addWidget(table);
}

