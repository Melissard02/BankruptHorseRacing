#include "TuiMainMenu.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

int TuiMainMenu::runMenu() {
  auto screen = ScreenInteractive::Fullscreen();

  int selected = 0;

  std::vector<std::string> options = {
    "Player Info",
    "Betting",
    "Horse",
    "Bank",
    "Start Race",
    "Save and Exit"
  };

  auto menu = Menu(&options, &selected);

  auto layout = Renderer(menu, [&] {
    return vbox({
        text("=== BANKRUPT RACING ===") | bold | center,
        separator(),
        menu->Render() | center
    });
  });

  screen.Loop(layout);

  return selected;
}

int TuiMainMenu::mainMenu() {
  return runMenu();
}
