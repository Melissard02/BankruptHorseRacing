#pragma once

#include "interfaces/IBankMenu.h"
#include "../../core/Player.h"
#include "../../core/Bank.h"

class TuiBankMenu : public IBankMenu {
public:
  TuiBankMenu(Player& player, Bank& bank)
      : player(player), bank(bank) {}

  void bankMenu() override;

private:
  int runMainMenu();
  void runTransferMenu();

  Player& player;
  Bank& bank;
};
