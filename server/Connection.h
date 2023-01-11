#pragma once

#include <vector>

using std::string;
using std::vector;

class Connection {
public:
    explicit Connection(int sockfd);

    void Run();

private:
    static constexpr int BUFFER_SIZE = 1024;
    static constexpr char LOGIN[] = "login";
    static constexpr char ALL_BOOKS[] = "allBooks";
    static constexpr char BOOK_CONTENT[] = "bookContent";
    int m_Sockfd;

private:
    static string SolveRequest(const string &request);

    static string Login(const string &username, const string &password);

    static string GetAllBooks();

    static string GetBookContent(int bookId);

    static vector<string> SplitString(std::stringstream &&str);
};
