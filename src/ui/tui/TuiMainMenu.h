#pragma once

#include "../../core/Bank.h"
#include "../../core/Better.h"
#include "../../core/Horse.h"
#include "../../core/Player.h"
#include "interfaces/IMainMenu.h"

#include <vector>

class TuiMainMenu : public IMainMenu {
public:
  TuiMainMenu(Player& player,
              std::vector<Horse>& horses,
              Bank& bank,
              std::vector<Better>& npcs)
      : player(player), horses(horses), bank(bank), npcs(npcs) {}

  int mainMenu() override;

private:
  int runMenu();

  Player& player;
  std::vector<Horse>& horses;
  Bank& bank;
  std::vector<Better>& npcs;
};
