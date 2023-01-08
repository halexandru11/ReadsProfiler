#include <bits/socket.h>
#include <sys/socket.h>
#include <csignal>
#include <netinet/in.h>
#include <cstring>
#include <thread>

#include "Server.h"
#include "Error.h"
#include "Database.h"
#include "Connection.h"

int Server::m_Sockfd;
bool Server::m_Disconnecting = false;

Server::Server(int port, int backlog) : m_Port(port), m_Backlog(backlog) {}

void Server::Start() const {
    m_Sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_Sockfd < 0) {
        Error::PrintWithErrno("Could not create socket");
        return;
    }
    signal(SIGTERM | SIGINT, &signalHandler);

    sockaddr_in addr{};
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(m_Port);

    if (bind(m_Sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        Error::PrintWithErrno("Could not bind the socket");
        return;
    }

    if (listen(m_Sockfd, m_Backlog) < 0) {
        Error::PrintWithErrno("Error occured while listening for new connections");
        return;
    }

    Database::Open();
    Database::CreateTablesIfNotExist();

    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sockfd = accept(m_Sockfd, reinterpret_cast<sockaddr*>(&client_addr), &client_addr_len);
        if (client_sockfd < 0) {
            if (m_Disconnecting == false) {
                Error::PrintWithErrno("Error occured while trying to accept client");
            }
            return;
        }

        auto con = Connection(client_sockfd);

        std::thread([&con]() {
            con.Run();
        }).detach();
    }
}

void Server::signalHandler(int) {
    m_Disconnecting = true;
    close(m_Sockfd);
    Database::Close();
}
