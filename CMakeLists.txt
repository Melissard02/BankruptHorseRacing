cmake_minimum_required(VERSION 3.10)
project(bankrupt)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/ftxui)

add_executable(bankrupt
        src/main.cpp

        # Core
        src/core/Horse.cpp
        src/core/Player.cpp
        src/core/Better.cpp
        src/core/Race.cpp
        src/core/Utils.cpp
        src/core/Bank.cpp

        # TUI Menus
        src/ui/tui/TuiMainMenu.cpp
        src/ui/tui/TuiPlayerMenu.cpp
        src/ui/tui/TuiBettingMenu.cpp
        src/ui/tui/TuiHorseMenu.cpp
        src/ui/tui/TuiBankMenu.cpp
        src/ui/tui/TuiRaceMenu.cpp
        src/ui/tui/RaceAnimation.cpp
)


target_link_libraries(${PROJECT_NAME}
        ftxui::component
        ftxui::screen
        ftxui::dom
)