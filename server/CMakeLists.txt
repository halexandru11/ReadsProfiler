cmake_minimum_required(VERSION 3.24)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp Server.cpp Server.h Connection.cpp Connection.h Error.cpp Error.h Database.cpp Database.h Book.cpp Book.h User.cpp User.h)
include_directories(/usr/include)

find_library(SQLITE3_LIBRARY NAMES sqlite3)

target_link_libraries(server ${SQLITE3_LIBRARY})
