/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *body;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *appBar;
    QHBoxLayout *horizontalLayout;
    QLabel *logo;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit;
    QPushButton *filterBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *loginBtn;
    QPushButton *logoutBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        body = new QFrame(centralwidget);
        body->setObjectName("body");
        body->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 221, 218);"));
        body->setFrameShape(QFrame::StyledPanel);
        body->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(body);
        gridLayout_2->setObjectName("gridLayout_2");
        scrollArea = new QScrollArea(body);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 560, 240));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);


        gridLayout->addWidget(body, 1, 0, 1, 1);

        appBar = new QFrame(centralwidget);
        appBar->setObjectName("appBar");
        appBar->setEnabled(true);
        appBar->setMinimumSize(QSize(582, 0));
        appBar->setMaximumSize(QSize(16777215, 70));
        QPalette palette;
        QBrush brush(QColor(98, 160, 234, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        appBar->setPalette(palette);
        appBar->setStyleSheet(QString::fromUtf8("background-color: rgb(98, 160, 234);"));
        appBar->setFrameShape(QFrame::StyledPanel);
        appBar->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(appBar);
        horizontalLayout->setObjectName("horizontalLayout");
        logo = new QLabel(appBar);
        logo->setObjectName("logo");
        logo->setMaximumSize(QSize(50, 16777215));
        logo->setPixmap(QPixmap(QString::fromUtf8(":/icon/images/white-logo.png")));
        logo->setScaledContents(true);

        horizontalLayout->addWidget(logo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lineEdit = new QLineEdit(appBar);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"font: 14pt \"Ubuntu\";\n"
"border-style: solid;\n"
"border-top-right-radius: 16;\n"
"border-top-left-radius: 16;\n"
"border-bottom-right-radius: 16;\n"
"border-bottom-left-radius: 16;"));

        horizontalLayout->addWidget(lineEdit);

        filterBtn = new QPushButton(appBar);
        filterBtn->setObjectName("filterBtn");
        filterBtn->setMinimumSize(QSize(30, 30));
        filterBtn->setMaximumSize(QSize(50, 50));
        filterBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(246, 97, 81, 0);\n"
"border-color: rgb(98, 160, 234);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/images/filter.png"), QSize(), QIcon::Normal, QIcon::Off);
        filterBtn->setIcon(icon);
        filterBtn->setIconSize(QSize(30, 30));
        filterBtn->setFlat(true);

        horizontalLayout->addWidget(filterBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        loginBtn = new QPushButton(appBar);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setMinimumSize(QSize(50, 0));
        loginBtn->setMaximumSize(QSize(50, 30));
        loginBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(246, 97, 81, 0);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(98, 160, 234);"));
        loginBtn->setIconSize(QSize(40, 40));
        loginBtn->setFlat(true);

        horizontalLayout->addWidget(loginBtn);

        logoutBtn = new QPushButton(appBar);
        logoutBtn->setObjectName("logoutBtn");
        logoutBtn->setMinimumSize(QSize(50, 0));
        logoutBtn->setMaximumSize(QSize(50, 50));
        logoutBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(246, 97, 81, 0);\n"
"border-color: rgb(98, 160, 234);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/images/logout.png"), QSize(), QIcon::Normal, QIcon::Off);
        logoutBtn->setIcon(icon1);
        logoutBtn->setIconSize(QSize(40, 40));
        logoutBtn->setFlat(true);

        horizontalLayout->addWidget(logoutBtn);


        gridLayout->addWidget(appBar, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        logo->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search...", nullptr));
        filterBtn->setText(QString());
        loginBtn->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        logoutBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
