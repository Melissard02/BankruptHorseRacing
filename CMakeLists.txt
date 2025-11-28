cmake_minimum_required(VERSION 4.0)
project(bankrupt)

set(CMAKE_CXX_STANDARD 20)

add_executable(bankrupt src/main.cpp
        src/core/Horse.cpp
        src/core/Player.cpp
        src/core/Better.cpp
        src/core/Race.cpp
        src/core/Utils.cpp
        src/ui/oldmenu/Menu.cpp
        src/ui/oldmenu/Menu.h
        src/core/Bank.cpp
        src/core/Bank.h
        src/ui/tui/TuiMainMenu.cpp
        src/ui/tui/TuiMainMenu.h
        src/ui/tui/TuiPlayerMenu.cpp
        src/ui/tui/TuiPlayerMenu.h
        src/ui/tui/TuiBettingMenu.cpp
        src/ui/tui/TuiBettingMenu.h
        src/ui/tui/TuiHorseMenu.cpp
        src/ui/tui/TuiBankMenu.cpp
        src/ui/tui/TuiBankMenu.h
        src/ui/tui/TuiRaceMenu.cpp
        src/ui/tui/TuiRaceMenu.h
        src/ui/tui/UI.h
        src/ui/oldmenu/TerminalMenu.h
)
