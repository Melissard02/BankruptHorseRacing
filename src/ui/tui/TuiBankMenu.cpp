#include "TuiBankMenu.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

TuiBankMenu::TuiBankMenu(ScreenInteractive& screen,
                         Player& player,
                         Bank& bank)
    : screen(screen), player(player), bank(bank) {}

void TuiBankMenu::bankMenu() {
    auto layout = Renderer([&] {
        return vbox({
            text("=== BANK ===") | bold | center,
            separator(),
            text("Balance: $" + std::to_string(player.getBalance())),
            text("Income:  $" + std::to_string(player.getIncome())),
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);
}
