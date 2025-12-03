#include "TuiPlayerMenu.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

int TuiPlayerMenu::runMenu() {
  auto screen = ScreenInteractive::Fullscreen();

  auto layout = Renderer([&] {
      // compute bet text
      std::string betText;
      if (player.getBetHorseIndex() >= 0 && player.getBetAmount() > 0) {
          int idx = player.getBetHorseIndex();
          betText = "Current Bet: $" + std::to_string(player.getBetAmount()) +
                    " on " + horses[idx].getName();
      } else {
          betText = "Current Bet: (none)";
      }

      return vbox({
          text("=== PLAYER ===") | bold | center,
          separator(),
          text("Name: " + player.getName()),
          text("Balance: $" + std::to_string(bank.getSavings())),
          text("Income: $" + std::to_string(player.getIncome())),
          text(betText),
          separator(),
          text("Press ESC to return") | dim | center
      }) | center;
  });

  screen.Loop(layout);
  return 0;
}

void TuiPlayerMenu::playerMenu() {
  runMenu();
}
