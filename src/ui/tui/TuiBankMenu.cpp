#include "TuiBankMenu.h"

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

// -----------------------------------------------------------
// Main Bank Menu
// -----------------------------------------------------------

int TuiBankMenu::runMainMenu() {
    auto screen = ScreenInteractive::Fullscreen();

    int selected = 0;
    std::vector<std::string> options = {
        "Transfer Funds",
        "Return"
    };

    auto menu = Menu(&options, &selected);

    auto layout = Renderer(menu, [&] {
        return vbox({
            text("=== BANK ===") | bold | center,
            separator(),
            text("Checking: $" + std::to_string(player.getBalance())),
            text("Savings:  $" + std::to_string(bank.getSavings())),
            text("Income:   $" + std::to_string(player.getIncome())),
            separator(),
            menu->Render() | center
        });
    });

    screen.Loop(layout);
    return selected;
}

// -----------------------------------------------------------
// Entry point
// -----------------------------------------------------------

void TuiBankMenu::bankMenu() {
    while (true) {
        int choice = runMainMenu();

        switch (choice) {
            case 0:
                runTransferMenu();
                break;

            case 1:
                return;
        }
    }
}

// -----------------------------------------------------------
// Transfer Funds Menu
// -----------------------------------------------------------

void TuiBankMenu::runTransferMenu() {
    auto screen = ScreenInteractive::Fullscreen();

    int selected = 0;
    std::vector<std::string> options = {
        "Transfer TO Checking",
        "Transfer TO Savings",
        "Cancel"
    };

    auto menu = Menu(&options, &selected);

    // FIRST screen: choose direction
    auto layout = Renderer(menu, [&] {
        return vbox({
            text("=== TRANSFER FUNDS ===") | bold | center,
            separator(),
            text("Checking: $" + std::to_string(player.getBalance())),
            text("Savings:  $" + std::to_string(bank.getSavings())),
            separator(),
            text("Select destination account:") | center,
            menu->Render() | center
        });
    });

    screen.Loop(layout);

    if (selected == 2)
        return;

    // SECOND screen: enter amount
    int amount = 0;

    // Input component for amount
    std::string amountStr = "";
    auto input = Input(&amountStr, "Enter amount");

    auto confirmLayout = Renderer(input, [&] {
        return vbox({
            text("=== ENTER AMOUNT ===") | bold | center,
            separator(),
            text("Checking: $" + std::to_string(player.getBalance())),
            text("Savings:  $" + std::to_string(bank.getSavings())),
            separator(),
            input->Render() | center,
            text("Press ENTER when done") | dim | center
        });
    });

    screen.Loop(confirmLayout);

    // Convert typed value
    try {
        amount = std::stoi(amountStr);
    } catch (...) {
        amount = -1;
    }

    // Validate
    bool toChecking = (selected == 0);

    bool ok = false;
    if (amount > 0) {
        if (toChecking && bank.getSavings() >= amount)
            ok = true;
        if (!toChecking && player.getBalance() >= amount)
            ok = true;
    }

    auto resultLayout = Renderer([&] {
        return vbox({
            text("=== RESULT ===") | bold | center,
            separator(),
            ok
                ? text("Transfer successful!") | color(Color::Green)
                : text("Transfer failed!") | color(Color::Red),
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    if (ok) {
        // Perform transfer
        bank.Transfer(player, amount, /*fromSavings*/ toChecking);
    }

    screen.Loop(resultLayout);
}
