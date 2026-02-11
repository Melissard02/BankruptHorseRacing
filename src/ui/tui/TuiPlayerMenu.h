#pragma once

#include "../../core/Player.h"
#include "../../core/Bank.h"
#include "../../core/Horse.h"
#include "interfaces/IPlayerMenu.h"

#include <ftxui/component/screen_interactive.hpp>

class TuiPlayerMenu : public IPlayerMenu {
public:
  TuiPlayerMenu(ftxui::ScreenInteractive& screen,
                Player& player,
                std::vector<Horse>& horses,
                Bank& bank);

  void playerMenu() override;

private:
  ftxui::ScreenInteractive& screen;
  Player& player;
  std::vector<Horse>& horses;
  Bank& bank;
};
