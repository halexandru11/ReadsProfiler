#pragma once

#include <string>

class Connection {
public:
    explicit Connection(int sockfd);

    void Send(const std::string& message) const;

    [[nodiscard]] std::string Receive() const;

private:
    int m_Sockfd;
    static constexpr int BUFFER_SIZE = 1024;
};
