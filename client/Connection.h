#pragma once

#include <string>

using std::string;

class Connection {
public:
    explicit Connection(int sockfd);

    void Send(const string& message) const;

    [[nodiscard]] string Receive() const;

private:
    int m_Sockfd;
    static constexpr int BUFFER_SIZE = 1024;
};
