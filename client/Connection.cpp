#include <sys/socket.h>

#include "Connection.h"
#include "Error.h"

Connection::Connection(int sockfd) : m_Sockfd(sockfd) {}

void Connection::Send(const string& message) const {
    if (send(m_Sockfd, message.c_str(), message.size(), 0) < 0) {
        Error::Print("Error sending message");
    }
}

string Connection::Receive() const {
    string output;
    char buffer[BUFFER_SIZE + 1];
    int totalSize;
    recv(m_Sockfd, &totalSize, sizeof(totalSize), 0);
    int receivedSize = 0;
    while(receivedSize < totalSize) {
        ssize_t n = recv(m_Sockfd, buffer, sizeof(buffer), 0);
        if (n < 0) {
            Error::Print("Error receiving message");
            break;
        }
        buffer[n] = '\0';
        output += buffer;
        receivedSize += n;
        if (n == 0) {
            Error::Print("Connection closed");
            break;
        }
    }
    return output;
}
