#pragma once

#include <QString>
#include <map>
#include <QList>

using std::map;

class User {
public:
    explicit User(int id, QString username, QString booksRead);

    explicit User(QString fromString);

    [[nodiscard]] int GetId() const { return m_Id; }

    [[nodiscard]] QString GetUsername() const { return m_Username; }

    [[nodiscard]] QString GetBooksRead() const { return m_BooksRead; }

    QList<QString> GetPreferedGen();

    QList<QString> GetPreferedSubgen();

    QString ToString() const;

private:
    int m_Id;
    QString m_Username, m_BooksRead;

public:
    map<QString, int> m_PrefGen, m_PrefSubgen;

private:
    void SetPref();
};
