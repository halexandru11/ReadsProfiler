#include <QStringList>
#include <iostream>
#include <vector>

#include "User.h"
#include "mainwindow.h"
#include "Error.h"

User::User(int id, QString username, QString booksRead)
        : m_Id(id), m_Username(username), m_BooksRead(booksRead) {
    SetPref();
}

User::User(QString fromString) {
    std::cout << "User is\n" << fromString.toStdString();
    std::cout.flush();

    QStringList list = fromString.split(':');
    if(list.size() == 3) {
        m_Id = list[0].toInt();
        m_Username = list[1];
        m_BooksRead = list[2];
    }
    else {
        m_Id = -1;
        m_Username = "";
        m_BooksRead = "";
    }
    SetPref();
}

QString User::ToString() const {
    return QString("%1:%2:%3").arg(m_Id).arg(m_Username).arg(m_BooksRead);
}

void User::SetPref() {
    QList<Book*> books = MainWindow::client.GetAllBooks();
    for(Book* book : books) {
        if(m_BooksRead.split(',').contains(QString("%1").arg(book->GetId())) == false) {
            continue;
        }
        for(const QString& genre : book->GetGenres()) {
            m_PrefGen[genre]++;
        }
        for(const QString& subgenre : book->GetSubgenres()) {
            m_PrefSubgen[subgenre]++;
        }
    }
}


QList<QString> User::GetPreferedGen() {
    std::vector<std::pair<QString, int>> vec(m_PrefGen.begin(), m_PrefGen.end());
    std::sort(vec.begin(), vec.end(), [](const auto &a, const auto &b) { return a.second > b.second; });

    QList<QString> top;
    for (int i = 0; i < vec.size(); ++i) {
        Error::PrintWithoutErrno(vec[i].first.toStdString());
        top.push_back(vec[i].first);
    }
    return top;
}

QList<QString> User::GetPreferedSubgen() {
    std::vector<std::pair<QString, int>> vec(m_PrefSubgen.begin(), m_PrefSubgen.end());
    std::sort(vec.begin(), vec.end(), [](const auto &a, const auto &b) { return a.second > b.second; });

    QList<QString> top;
    for (int i = 0; i < vec.size(); ++i) {
        Error::PrintWithoutErrno(vec[i].first.toStdString());
        top.push_back(vec[i].first);
    }
    return top;
}
