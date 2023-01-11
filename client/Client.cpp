#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <fstream>

#include "Client.h"
#include "Connection.h"
#include "Error.h"

Client::Client(string serverIp, int serverPort) : m_ServerIp(std::move(serverIp)), m_ServerPort(serverPort) {}

bool Client::Connect() {
    m_Sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_Sockfd < 0) {
        Error::Print("Could not create socket");
        return false;
    }

    sockaddr_in addr{};
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(m_ServerIp.c_str());
    addr.sin_port = htons(m_ServerPort);
    if (connect(m_Sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        Error::Print("Could not connect to server");
        return false;
    }

    return true;
}

void Client::Login(const string& username, const string& password) {
    string request = "login:" + username + ":" + password;
    m_User = User(QString::fromStdString(SendReceive(request)));
}

void Client::GetAllBooksFromServer() {
    if(m_Books.empty() == false) {
        return;
    }

    string request = "allBooks";
    QString response = QString::fromStdString(SendReceive(request));
    m_Books.resize(0);
    for(const QString& bookString : response.split('|')) {
        Error::PrintWithoutErrno(bookString.toStdString());
        m_Books.push_back(new Book(bookString));
    }
}

QList<Book*> Client::GetBooksGenre(string genre) {
    QList<Book*> output;
    for(Book* book : m_Books) {
        Error::PrintWithoutErrno(QString("BookId is %1").arg(book->GetId()).toStdString());
        if(book->GetGenresAsString().contains(QString::fromStdString(genre))) {
            output.push_back(book);
        }
    }
    return output;
}

QList<Book*> Client::GetBooksSubGenre(string subgenre) {
    QList<Book*> output;
    for(Book* book : m_Books) {
        if(book->GetSubgenresAsString().contains(QString::fromStdString(subgenre))) {
            output.push_back(book);
        }
    }
    return output;
}

QList<Book*> Client::GetBooksSugesstions() {
    QList<Book*> output;
    std::sort(m_Books.begin(), m_Books.end(),
        [](const Book* A, const Book* B) {
            return A->GetRating() > B->GetRating();
    });
    for(int i = 0; i < 20; ++i) {
        output.push_back(m_Books[i]);
    }
    return output;
}

QList<Book*> Client::GetBooksSearch(QString search) {
    search = search.toLower();
    QList<Book*> output;
    for(Book* book : m_Books) {
        if(book->GetTitle().toLower().contains(search)
                || book->GetGenresAsString().toLower().contains(search)
                || book->GetISBN().toLower().contains(search)
                || book->GetSubgenresAsString().toLower().contains(search)) {
            output.push_back(book);
        }
    }
    return output;
}

void Client::SetUserModifyGen(QString gen, bool add) {
    if(add) {
        ++m_User.m_PrefGen[gen];
    }
    else {
        --m_User.m_PrefGen[gen];
        if(m_User.m_PrefGen[gen] <= 0) {
            m_User.m_PrefGen.erase(gen);
        }
    }
}

void Client::SetUserModifySubgen(QString subgen, bool add) {
    if(add) {
        ++m_User.m_PrefSubgen[subgen];
    }
    else {
        --m_User.m_PrefSubgen[subgen];
        if(m_User.m_PrefSubgen[subgen] <= 0) {
            m_User.m_PrefSubgen.erase(subgen);
        }
    }
}

void Client::DownloadBook(int bookId) {
    string idString = std::to_string(bookId);
    string request = "bookContent:" + idString;
    QString response = QString::fromStdString(SendReceive(request));
    Error::PrintWithoutErrno(response.toStdString());
    Error::PrintWithoutErrno("Write to file");
    std::ofstream fout(idString + ".txt");
    fout << response.toStdString();
    Error::PrintWithoutErrno("Done writing");
    fout.close();
}

[[nodiscard]] string Client::SendReceive(const string& request) {
    Connect();
    auto con = Connection(m_Sockfd);
    con.Send(request);
    string response = con.Receive();
    close(m_Sockfd);
    return response;
}

