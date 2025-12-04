#include "TuiBettingMenu.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

void TuiBettingMenu::betMenu() {
    int selected = 0;
    std::vector<std::string> options = {
        "Show Horses",
        "Show Bets",
        "Return"
    };

    auto menu = Menu(&options, &selected);

    auto layout = Renderer(menu, [&] {
        return vbox({
        text("=== BET MENU ====") | bold | center,
            separator(),
            menu->Render() | center
        });
    });

    screen.Loop(layout);

    if (selected == 0) {
        showHorseList();
    } else if (selected == 1) {
        placeBetMenu();
    }
}

TuiBettingMenu::TuiBettingMenu(ScreenInteractive& screen,
                               Player& player,
                               std::vector<Horse>& horses)
    : screen(screen), player(player), horses(horses) {}

void TuiBettingMenu::showHorseList() {
    auto layout = Renderer([&] {
        std::vector<Element> list;

        for (auto& h : horses)
            list.push_back(text("• " + h.getName()));

        return vbox({
            text("=== HORSE LIST ===") | bold | center,
            separator(),
            vbox(list) | center,
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);
}


void TuiBettingMenu::placeBetMenu() {
    int selected = 0;

    // Step 1: Choose horse
    std::vector<std::string> names;
    for (auto& h : horses)
        names.push_back(h.getName());

    auto horseMenu = Menu(&names, &selected);

    auto horseLayout = Renderer(horseMenu, [&] {
        return vbox({
            text("=== SELECT HORSE TO BET ON ===") | bold | center,
            separator(),
            horseMenu->Render() | center,
            separator(),
            text("Press Enter to select, ESC to cancel") | dim | center
        });
    });

    screen.Loop(horseLayout);

    int horseIndex = selected;

    // Step 2: Ask for bet amount
    std::string betAmountString = "50"; // Minimum

    auto input = Input(&betAmountString, "Enter Bet");

    int betAmount = std::stoi(betAmountString);

    auto betLayout = Renderer(input, [&] {
        return vbox({
            text("=== ENTER BET AMOUNT ===") | bold | center,
            separator(),
            text("Minimum Bet: $50") | dim,
            separator(),
            input->Render() | center,
            separator(),
            text("Press Enter to confirm, ESC to cancel") | dim | center
        });
    });

    screen.Loop(betLayout);

    // Step 3: Place the actual bet
    bool success = player.placeBet(betAmount, horseIndex);

    // Step 4: Show result screen
    auto resultLayout = Renderer([&] {
        return vbox({
            text(success ? "Bet Placed Successfully!" : "Bet Failed!")
                | bold
                | center,
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(resultLayout);
}

