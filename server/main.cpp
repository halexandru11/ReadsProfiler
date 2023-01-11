#include "Server.h"

int main() {
    auto server = Server(8112, 20);
    server.Start();

    return 0;
}