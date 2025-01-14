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
    std::cerr << "Error code " << errno << ": " << strerror(errno) << std::endl;
}

void Error::PrintWithoutErrno(std::string&& description) {
    std::cout << description.size() << std::endl;
    while (description.back() == ' ' || description.back() == '.') {
        description.pop_back();
    }
    std::cout << description << std::endl;
}

void Error::PrintWithoutErrno(std::string& description) {
    std::cout << description.size() << std::endl;
    while (description.back() == ' ' || description.back() == '.') {
        description.pop_back();
    }
    std::cout << description << std::endl;
}
