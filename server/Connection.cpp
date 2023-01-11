#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <csignal>
#include <sstream>

#include "Connection.h"
#include "Error.h"
#include "Database.h"

Connection::Connection(int sockfd) : m_Sockfd(sockfd) {}

void Connection::Run() {
    char buffer[BUFFER_SIZE];
    ssize_t n = recv(m_Sockfd, buffer, BUFFER_SIZE, 0);
    if (n < 0) {
        Error::PrintWithErrno("Could not receive request from client");
    } else if (n == 0) {
        // Connection closed
    }

    string responseString = SolveRequest(buffer);

    int totalSize = (int) responseString.size();
    std::cout << totalSize << std::endl;
    std::cout << responseString << std::endl;
    int sentSize = 0;
    send(m_Sockfd, &totalSize, sizeof(totalSize), 0);
    while (sentSize < totalSize) {
        int sizeToSend = std::min(totalSize - sentSize, 1024);
        char newBuffer[sizeToSend + 1];
        strncpy(newBuffer, responseString.data() + sentSize, sizeToSend);
        newBuffer[sizeToSend] = '\0';
        int size = (int) send(m_Sockfd, newBuffer, sizeToSend + 1, 0);
        if (size < 0) {
            Error::PrintWithErrno("Could not send response to client");
            break;
        }
        if (size < 1024) {
            break;
        }
        sentSize += 1024;
    }

    // Close the socket
    close(m_Sockfd);
}

string Connection::SolveRequest(const std::string &request) {
    vector<string> tokens = SplitString(std::stringstream(request));

    if (tokens[0] == LOGIN) {
        if (tokens.size() != 3) {
            Error::Print("Bad number of arguments(expected 2). i.e `login username password`");
            return "";
        }
        return Login(tokens[1], tokens[2]);
    } else if (tokens[0] == ALL_BOOKS) {
        return GetAllBooks();
    } else if (tokens[0] == BOOK_CONTENT) {
        if (tokens.size() != 2) {
        }
        return GetBookContent(1);
    }
}

string Connection::Login(const string &username, const string &password) {
    User user = Database::GetUserIdByUsernameAndPassword(username, password);
    if (user.GetId() == -1) {
        Error::Print("Username or password are wrong");
        return "";
    }
    return user.ToString();
}

string Connection::GetAllBooks() {
    vector<Book> books = Database::GetAllBooks();
    if (books.empty()) {
        return "";
    }
    string output;
    for (const Book &book: books) {
        output += book.ToString();
        output += "|";
    }
    return output.substr(0, output.size() - 1);
}

vector<string> Connection::SplitString(std::stringstream &&str) {
    vector<string> output;
    string token;
    while (std::getline(str, token, ':')) {
        output.push_back(token);
    }
    return output;
}

string Connection::GetBookContent(int bookId) {
    string response = Database::GetBookContent(bookId);
    std::cout << response << std::endl;
    return response;
}

