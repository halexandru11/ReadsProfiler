#pragma once

#include <string>

class Error {
public:
    Error() = delete;

    static void Print(std::string&& description);

    static void PrintWithoutErrno(std::string&& description);

    static void PrintWithoutErrno(std::string& description);
};
