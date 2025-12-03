cmake_minimum_required(VERSION 3.10)
project(bankrupt)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/ftxui)

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
        src/ui/oldmenu/TerminalMenu.h
        src/ui/oldmenu/TerminalMenu.cpp
        src/ui/tui/TuiHorseMenu.h
        src/ui/tui/interfaces/IMainMenu.h
        src/ui/tui/interfaces/IPlayerMenu.h
        src/ui/tui/interfaces/IHorseMenu.h
        src/ui/tui/interfaces/IBankMenu.h
        src/ui/tui/interfaces/IBettingMenu.h
        src/ui/tui/interfaces/IRaceMenu.h
        src/ui/tui/RaceAnimation.h
        src/ui/tui/RaceAnimation.cpp
)

target_link_libraries(${PROJECT_NAME}
        ftxui::component
        ftxui::screen
        ftxui::dom
)