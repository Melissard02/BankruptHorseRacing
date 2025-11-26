cmake_minimum_required(VERSION 4.0)
project(bankrupt)

set(CMAKE_CXX_STANDARD 20)

add_executable(bankrupt src/main.cpp
        src/Horse.cpp
        src/Player.cpp
        src/Better.cpp
        src/Race.cpp
        src/Utils.cpp
        src/Menu.cpp
        src/Menu.h
        src/Bank.cpp
        src/Bank.h
)
