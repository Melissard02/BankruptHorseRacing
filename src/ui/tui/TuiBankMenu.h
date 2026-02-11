#pragma once

#include "../../core/Bank.h"
#include "../../core/Player.h"
#include "interfaces/IBankMenu.h"

#include <ftxui/component/screen_interactive.hpp>

class TuiBankMenu : public IBankMenu {
public:
  TuiBankMenu(ftxui::ScreenInteractive& screen,
              Player& player,
              Bank& bank);

  void bankMenu() override;

private:
  ftxui::ScreenInteractive& screen;
  Player& player;
  Bank& bank;
};
