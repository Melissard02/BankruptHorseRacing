#pragma once

#include "interfaces/IBettingMenu.h"
#include "../../core/Player.h"
#include "../../core/Horse.h"

#include <vector>

class TuiBettingMenu : public IBetMenu {
public:
  TuiBettingMenu(Player& player, std::vector<Horse>& horses)
      : player(player), horses(horses) {}

  void betMenu() override;

private:
  int runMainMenu();
  void showHorseList();
  void runPlaceBetMenu();

  Player& player;
  std::vector<Horse>& horses;
};
