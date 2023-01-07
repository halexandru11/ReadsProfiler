#include <iostream>
#include <cstring>

#include "Error.h"

void Error::Print(std::string&& description) {
    while (description.back() == ' ' || description.back() == '.') {
        description.pop_back();
    }
    std::cerr << description;
    if (strchr(" \t", description.back()) == nullptr) {
        std::cerr << ". ";
    }
    std::cout << "Error code " << errno << ": " << strerror(errno) << "\n";
}