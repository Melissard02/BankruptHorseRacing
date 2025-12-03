#include "TuiHorseMenu.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

// -----------------------------------------------------------
// Main Horse Menu
// -----------------------------------------------------------

int TuiHorseMenu::runMainMenu() {
    auto screen = ScreenInteractive::Fullscreen();

    int selected = 0;

    std::vector<std::string> options = {
        "Horse List",
        "All Horse Stats",
        "View Single Horse",
        "Return"
    };

    auto menu = Menu(&options, &selected);

    auto layout = Renderer(menu, [&] {
        return vbox({
            text("=== HORSE MENU ===") | bold | center,
            separator(),
            menu->Render() | center
        });
    });

    screen.Loop(layout);
    return selected;
}

// -----------------------------------------------------------
// PUBLIC ENTRYPOINT
// -----------------------------------------------------------

void TuiHorseMenu::horseMenu() {
    while (true) {
        int choice = runMainMenu();

        switch (choice) {
            case 0:
                showHorseList();
                break;
            case 1:
                showAllStats();
                break;
            case 2:
                showSingleHorsePrompt();
                break;
            case 3:
                return;  // exit to main menu
        }
    }
}

// -----------------------------------------------------------
// Horse List Screen
// -----------------------------------------------------------

void TuiHorseMenu::showHorseList() {
    auto screen = ScreenInteractive::Fullscreen();

    auto layout = Renderer([&] {
        std::vector<Element> items;
        for (auto& h : horses) {
            items.push_back(text("• " + h.getName()));
        }

        return vbox({
            text("=== HORSES ===") | bold | center,
            separator(),
            vbox(items) | center,
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);
}

// -----------------------------------------------------------
// All Horse Stats — full breakdown for every horse
// -----------------------------------------------------------
void TuiHorseMenu::showAllStats() {
    auto screen = ScreenInteractive::Fullscreen();

    auto layout = Renderer([&] {
        std::vector<Element> stats;

        for (auto& h : horses) {
            float rate = h.winRate() * 100.0f;
            std::string rateText = std::to_string(rate).substr(0, 5) + "%";

            stats.push_back(
                vbox({
                    text(h.getName()) | bold,
                    text("Legendary: " + std::string(h.isLegendary() ? "YES" : "No")),
                    text("Speed: " + std::to_string(h.getSpeed())),
                    text("Stamina: " + std::to_string(h.getStamina())),
                    text("Popularity: " + std::to_string(h.getPopularity())),
                    text("Luck: " + std::to_string(h.getLuck())),
                    text("Wins: " + std::to_string(h.getWins())),
                    text("Races: " + std::to_string(h.getRaces())),
                    text("Win Rate: " + rateText),
                    separator()
                })
            );
        }

        return vbox({
            text("=== ALL HORSE STATS ===") | bold | center,
            separator(),
            vbox(stats) | center,
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);
}

// -----------------------------------------------------------
// Single Horse View Stats
// -----------------------------------------------------------
void TuiHorseMenu::showSingleHorse(int index) {
    if (index < 0 || index >= (int)horses.size())
        return;

    auto& h = horses[index];
    auto screen = ScreenInteractive::Fullscreen();

    auto layout = Renderer([&] {
        // win rate as percentage
        float percentage = h.winRate() * 100.0f;
        std::string rateText = std::to_string(percentage).substr(0, 4) + "%";

        return vbox({
            text("=== HORSE DETAILS ===") | bold | center,
            separator(),
            text("Name: " + h.getName()) | bold,
            text("Legendary: " + std::string(h.isLegendary() ? "YES" : "No")),
            separator(),
            text("Speed: " + std::to_string(h.getSpeed())),
            text("Stamina: " + std::to_string(h.getStamina())),
            text("Popularity: " + std::to_string(h.getPopularity())),
            text("Luck: " + std::to_string(h.getLuck())),
            separator(),
            text("Wins: " + std::to_string(h.getWins())),
            text("Races: " + std::to_string(h.getRaces())),
            text("Win Rate: " + rateText),
            separator(),
            text("Press ESC to return") | dim | center
        }) | center;
    });

    screen.Loop(layout);
}

// -----------------------------------------------------------
// Prompt: select which horse to view, I hate this thing but what are you going to do
// -----------------------------------------------------------
void TuiHorseMenu::showSingleHorsePrompt() {
    auto screen = ScreenInteractive::Fullscreen();

    int selected = 0;

    // Build a list of horse names
    std::vector<std::string> names;
    for (auto& h : horses) {
        names.push_back(h.getName());
    }

    // FTXUI menu for selection
    auto menu = Menu(&names, &selected);

    auto layout = Renderer(menu, [&] {
        return vbox({
            text("=== SELECT A HORSE ===") | bold | center,
            separator(),
            menu->Render() | center,
            separator(),
            text("Press ENTER to choose a horse") | dim | center,
            text("Press ESC to return") | dim | center
        });
    });

    // Runs until ESC or ENTER is pressed
    screen.Loop(layout);

    // If ESC was used, selected index stays valid but never triggers selection
    if (selected >= 0 && selected < (int)horses.size()) {
        showSingleHorse(selected);
    }
}

