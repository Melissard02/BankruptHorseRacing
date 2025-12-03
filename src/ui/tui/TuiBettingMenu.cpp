#include "TuiBettingMenu.h"

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

// -----------------------------------------------------------
// Main Betting Menu
// -----------------------------------------------------------

int TuiBettingMenu::runMainMenu() {
    auto screen = ScreenInteractive::Fullscreen();

    int selected = 0;

    std::vector<std::string> options = {
        "View Horses",
        "Place Bet",
        "Return"
    };

    auto menu = Menu(&options, &selected);

    auto layout = Renderer(menu, [&] {
        return vbox({
            text("=== BETTING ===") | bold | center,
            separator(),
            menu->Render() | center
        });
    });

    screen.Loop(layout);
    return selected;
}

// -----------------------------------------------------------
// Entrypoint
// -----------------------------------------------------------

void TuiBettingMenu::betMenu() {
    while (true) {
        int choice = runMainMenu();

        switch (choice) {
            case 0:
                showHorseList();
                break;
            case 1:
                runPlaceBetMenu();
                break;
            case 2:
                return;
        }
    }
}

// -----------------------------------------------------------
// Show horse stats (non-interactive)
// -----------------------------------------------------------

void TuiBettingMenu::showHorseList() {
    auto screen = ScreenInteractive::Fullscreen();

    auto layout = Renderer([&] {
        std::vector<Element> items;

        for (auto& h : horses) {
            items.push_back(vbox({
                text(h.getName()) | bold,
                text("Speed: " + std::to_string(h.getSpeed())),
                text("Stamina: " + std::to_string(h.getStamina())),
                text("Popularity: " + std::to_string(h.getPopularity())),
                text("Luck: " + std::to_string(h.getLuck())),
                separator()
            }));
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
// Place Bet Flow
// -----------------------------------------------------------

void TuiBettingMenu::runPlaceBetMenu() {
    auto screen = ScreenInteractive::Fullscreen();

    // STEP 1: Show only non-legendary horses
    std::vector<int> bettable;
    std::vector<std::string> names;

    for (int i = 0; i < (int)horses.size(); i++) {
        if (!horses[i].isLegendary()) {
            bettable.push_back(i);
            names.push_back(horses[i].getName());
        }
    }

    if (bettable.empty()) {
        auto layout = Renderer([] {
            return vbox({
                text("No eligible horses to bet on!") | bold | color(Color::Red),
                separator(),
                text("Press ESC to return") | dim | center
            });
        });
        screen.Loop(layout);
        return;
    }

    // STEP 2: Choose horse
    int selected = 0;
    auto menu = Menu(&names, &selected);

    auto chooseLayout = Renderer(menu, [&] {
        return vbox({
            text("=== PLACE BET ===") | bold | center,
            separator(),
            menu->Render() | center,
            separator(),
            text("Select a horse (ENTER)") | dim | center
        });
    });

    screen.Loop(chooseLayout);

    int realHorseIndex = bettable[selected];

    // STEP 3: Enter amount
    std::string amountStr = "";
    auto input = Input(&amountStr, "Enter bet amount");

    auto amountLayout = Renderer(input, [&] {
        return vbox({
            text("=== BET AMOUNT ===") | bold | center,
            separator(),
            text("Your Balance: $" + std::to_string(player.getBalance())),
            separator(),
            input->Render() | center,
            text("Press ENTER when done") | dim | center
        });
    });

    screen.Loop(amountLayout);

    int amount = 0;
    try {
        amount = std::stoi(amountStr);
    } catch (...) {
        amount = 0;
    }

    // STEP 4: Validation
    bool success = false;

    if (amount >= 50 && amount <= player.getBalance()) {
        success = player.placeBet(amount, realHorseIndex); // ✔ same as old code
    }

    // STEP 5: Result screen
    auto resultLayout = Renderer([&] {
        return vbox({
            text(success
                 ? "Bet Placed Successfully!"
                 : "Failed to Place Bet!") |
                bold |
                color(success ? Color::Green : Color::Red),
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(resultLayout);
}
