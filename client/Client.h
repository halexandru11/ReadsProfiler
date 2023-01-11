#pragma once

#include <string>
#include <QList>
#include <QStringList>

#include "Book.h"
#include "User.h"

using std::string;

class Client {
public:
    Client(string serverIp, int serverPort);

    User GetUser() const { return m_User; }

    void SetUserModifyGen(QString gen, bool add = true);

    void SetUserModifySubgen(QString subgen, bool add = true);

    void Login(const string& username, const string& password);

    void GetAllBooksFromServer();

    void DownloadBook(int bookId);

    QList<Book*> GetAllBooks() { return m_Books; }

    QList<Book*> GetBooksGenre(string genre);

    QList<Book*> GetBooksSubGenre(string subgenre);

    QList<Book*> GetBooksSugesstions();

    QList<Book*> GetBooksSearch(QString search);

private:
    int m_Sockfd = 0;
    string m_ServerIp;
    int m_ServerPort;
    User m_User = User(-1, "", "");
    QList<Book*> m_Books;

private:
    bool Connect();

    [[nodiscard]] string SendReceive(const string& request);
};
