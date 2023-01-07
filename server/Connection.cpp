#include <cstdio>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <csignal>
#include <sstream>
#include <sqlite3.h>

#include "Connection.h"
#include "Error.h"

Connection::Connection(int sockfd) : m_Sockfd(sockfd) {}

void Connection::Run() const {
    char buffer[BUFFER_SIZE];
    ssize_t n = recv(m_Sockfd, buffer, BUFFER_SIZE, 0);
    if (n < 0) {
        Error::PrintWithErrno("Could not receive request from client");
    } else if (n == 0) {
        // Connection closed
    }

    // TODO: Solve client request
//    std::cout << "Received " << n << " bytes: " << buffer << std::endl;
    SolveRequest(buffer);

    const char* response = "ACK\n";
    if (send(m_Sockfd, response, std::strlen(response), 0) < 0) {
        Error::PrintWithErrno("Could not send response to client");
    }

    // Close the socket
    close(m_Sockfd);
}

void Connection::SolveRequest(const std::string& request) {
    vector<string> tokens = SplitString(std::stringstream(request));

    if (tokens[0] == LOGIN) {
        if (tokens.size() != 3) {
            Error::Print("Bad number of arguments(expected 2). i.e: `login username password`");
            return;
        }
        Login(tokens[1], tokens[2]);
    }
}

void Connection::Login(const string& username, const string& password) {
    string loginReq = "SELECT id FROM users "
                      "WHERE username=\"" + username + "\" AND password=\"" + password + "\";";
    char* errMsg;
    sqlite3* db;
    sqlite3_exec(db, loginReq.c_str(), nullptr, nullptr, &errMsg);
}

vector<string> Connection::SplitString(std::stringstream&& str) {
    vector<string> output;
    string token;
    while (std::getline(str, token, ':')) {
        output.push_back(token);
    }
    return output;
}

