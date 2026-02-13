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
        src/LoadScreen.cpp
        src/LoadScreen.h
        src/Database.cpp
        src/Database.h
        src/GameSave.h
)


# TEST FOR SQLITE
find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(bankrupt PRIVATE unofficial::sqlite3::sqlite3)

add_executable(sqlite_test
        src/sqlite_test.cpp
        src/Database.cpp
)
target_link_libraries(sqlite_test PRIVATE unofficial::sqlite3::sqlite3)
