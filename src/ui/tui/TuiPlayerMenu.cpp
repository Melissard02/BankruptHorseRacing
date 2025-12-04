#include "TuiPlayerMenu.h"

#include <ftxui/component/component.hpp>
// #include <ftxui/component/catch_event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

TuiPlayerMenu::TuiPlayerMenu(ScreenInteractive& screen,
                             Player& player,
                             std::vector<Horse>& horses,
                             Bank& bank)
    : screen(screen), player(player), horses(horses), bank(bank) {}

void TuiPlayerMenu::playerMenu() {
    bool done = false;

    auto layout = Renderer([&] {
        if (done)
            screen.ExitLoopClosure()();   // <- FIX
        return vbox({
            text("=== PLAYER INFO ===") | bold | center,
            separator(),
            text("Name: " + player.getName()),
            text("Balance: $" + std::to_string(player.getBalance())),
            text("Income: $" + std::to_string(player.getIncome())),
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    auto component = layout | CatchEvent([&](Event event) {
        if (event == Event::Escape) {
            done = true;
            screen.Post(Event::Custom);    // <- FIX
            return true;
        }
        return false;
    });

    screen.Loop(component);
}

