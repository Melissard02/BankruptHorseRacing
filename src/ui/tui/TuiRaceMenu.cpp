#include "TuiRaceMenu.h"
#include "RaceAnimation.h"   // will implement after

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

// -----------------------------------------------------------
// Race Menu Navigation
// -----------------------------------------------------------

int TuiRaceMenu::runMainMenu() {
    auto screen = ScreenInteractive::Fullscreen();
    int selected = 0;

    std::vector<std::string> options = {
        "Start Race",
        "Return"
    };

    auto menu = Menu(&options, &selected);

    auto layout = Renderer(menu, [&] {
        std::vector<Element> horseList;

        for (auto& h : horses) {
            horseList.push_back(text("• " + h.getName()));
        }

        return vbox({
            text("=== RACE DAY ===") | bold | center,
            separator(),
            text("Featured Racers:") | bold,
            vbox(horseList) | center,
            separator(),
            legendarySpawned
                ? text("⚡ LEGENDARY Horse Joined: " + legendaryName + " ⚡")
                      | bold | color(Color::Yellow) | center
                : text(""),
            separator(),
            menu->Render() | center
        });
    });

    screen.Loop(layout);
    return selected;
}

// -----------------------------------------------------------
// Public entry point
// -----------------------------------------------------------

void TuiRaceMenu::raceMenu() {
    while (true) {
        int choice = runMainMenu();

        if (choice == 0) {
            // Start race → call animation handler
            RaceAnimation(player, horses, npcs, legendarySpawned, legendaryName);
        }

        if (choice == 1)
            return;
    }
}

// -----------------------------------------------------------
// Simple “View Racers” Screen (if needed later)
// -----------------------------------------------------------

void TuiRaceMenu::showHorsesScreen() {
    auto screen = ScreenInteractive::Fullscreen();

    auto layout = Renderer([&] {
        std::vector<Element> horseList;
        for (auto& h : horses) {
            horseList.push_back(text("• " + h.getName()));
        }

        return vbox({
            text("=== RACERS ===") | bold | center,
            separator(),
            vbox(horseList) | center,
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);
}
