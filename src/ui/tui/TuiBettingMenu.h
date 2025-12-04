#pragma once

#include "../../core/Player.h"
#include "../../core/Horse.h"
#include "interfaces/IBettingMenu.h"

#include <ftxui/component/screen_interactive.hpp>

class TuiBettingMenu : public IBetMenu {
public:
  TuiBettingMenu(ftxui::ScreenInteractive& screen,
                 Player& player,
                 std::vector<Horse>& horses);

  void betMenu() override;

private:
  void showHorseList();
  void placeBetMenu();

  ftxui::ScreenInteractive& screen;
  Player& player;
  std::vector<Horse>& horses;
};
