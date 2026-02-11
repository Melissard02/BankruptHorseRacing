#pragma once

#include "../../core/Bank.h"
#include "../../core/Better.h"
#include "../../core/Horse.h"
#include "../../core/Player.h"

#include "ftxui/component/screen_interactive.hpp"
#include "interfaces/IMainMenu.h"

#include <vector>

class TuiMainMenu : public IMainMenu {
public:
  TuiMainMenu(ftxui::ScreenInteractive& screen,
              Player& player,
              std::vector<Horse>& horses,
              Bank& bank,
              std::vector<Better>& npcs)
      : screen(screen), player(player), horses(horses), bank(bank), npcs(npcs) {}

  int mainMenu() override;

private:
  ftxui::ScreenInteractive& screen;
  Player& player;
  std::vector<Horse>& horses;
  Bank& bank;
  std::vector<Better>& npcs;
};
