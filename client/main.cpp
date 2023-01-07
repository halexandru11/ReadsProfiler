#include <iostream>

#include "Client.h"

int main() {
    auto client = Client("127.0.0.1", 8083);
    while (true) {
        std::string username, password;
        std::cin >> username >> password;
        std::cout << "Server response: " << client.Login(username, password);
    }
}