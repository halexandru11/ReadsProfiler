#pragma once

#include <vector>

using std::string;
using std::vector;

class Connection {
public:
    explicit Connection(int sockfd);

    void Run() const;

private:
    static constexpr int BUFFER_SIZE = 1024;
    static constexpr char LOGIN[] = "login";
    int m_Sockfd;

private:
    static void SolveRequest(const string& request);

    void Login(const string& username, const string& password);

    static vector<string> SplitString(std::stringstream&& str);
};
