#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

#include "Client.h"
#include "Connection.h"
#include "Error.h"

Client::Client(std::string serverIp, int serverPort) : m_ServerIp(std::move(serverIp)), m_ServerPort(serverPort) {}

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

std::string Client::Login(const std::string& username, const std::string& password) {
    std::string request = "login:" + username + ":" + password;
    return SendReceive(request);
}

[[nodiscard]] std::string Client::SendReceive(const std::string& request) {
    Connect();
    auto con = Connection(m_Sockfd);
    con.Send(request);
    std::string response = con.Receive();
    close(m_Sockfd);
    return response;
}

