#pragma once

#include "../../core/Bank.h"
#include "../../core/Horse.h"
#include "../../core/Player.h"
#include "interfaces/IPlayerMenu.h"

#include <vector>

class TuiPlayerMenu : public IPlayerMenu {
public:
  TuiPlayerMenu(Player& player,
                std::vector<Horse>& horses,
                Bank& bank)
      : player(player), horses(horses), bank(bank) {}

  void playerMenu() override;

private:
  int runMenu();

  Player& player;
  std::vector<Horse>& horses;
  Bank& bank;
};
