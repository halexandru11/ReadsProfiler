#include <iostream>
#include <cstring>

#include "Error.h"

using std::cerr;

void Error::PrintWithErrno(string&& description) {
    while (description.back() == ' ' || description.back() == '.') {
        description.pop_back();
    }
    cerr << description;
    if (strchr(" \t", description.back()) == nullptr) {
        cerr << ". ";
    }
    cerr << "Error code " << errno << ": " << strerror(errno) << "\n";
}

void Error::Print(string&& description) {
    cerr << description << "\n";
}
