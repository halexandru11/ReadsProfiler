#include <sys/socket.h>

#include "Connection.h"
#include "Error.h"

Connection::Connection(int sockfd) : m_Sockfd(sockfd) {}

void Connection::Send(const std::string& message) const {
    if (send(m_Sockfd, message.c_str(), message.size(), 0) < 0) {
        Error::Print("Error sending message");
    }
}

std::string Connection::Receive() const {
    char buffer[BUFFER_SIZE];
    ssize_t n = recv(m_Sockfd, buffer, BUFFER_SIZE, 0);
    if (n < 0) {
        Error::Print("Error receiving message");
        return "";
    }
    if (n == 0) {
        Error::Print("Connection closed");
        return "";
    }
    return buffer;
}