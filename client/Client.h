#pragma once

#include <string>

class Client {
public:
    Client(std::string serverIp, int serverPort);


    std::string Login(const std::string& username, const std::string& password);

private:
    int m_Sockfd = 0;
    std::string m_ServerIp;
    int m_ServerPort;

private:
    bool Connect();

    [[nodiscard]] std::string SendReceive(const std::string& request);
};
