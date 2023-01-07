#pragma once

#include <string>

using std::string;

class Error {
public:
    Error() = delete;

    static void PrintWithErrno(string&& description);

    static void Print(string&& description);
};
