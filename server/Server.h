#pragma once

class Server {
public:
    explicit Server(int port, int backlog);

    void Start() const;

private:
    static int m_Sockfd;
    static bool m_Disconnecting;
    int m_Port;
    int m_Backlog;

private:
    static void signalHandler(int sig);
};