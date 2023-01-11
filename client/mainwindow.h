#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include "bookwidget.h"
#include "Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static Client client;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onCellClicked(int row, int column);
    void handleButtonClick();
    void handleLoginButtonClick();
    void Populate();
    void Search();

private:
    Ui::MainWindow *ui;
    QTableWidget* table = nullptr;

private:
    void GetBooks(QList<BookWidget*>& books);
};

#endif // MAINWINDOW_H
