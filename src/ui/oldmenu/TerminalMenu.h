# pragma once
#include "../tui/UI.h"

#include <vector>

class TerminalMenu : public UI {
public:
  TerminalMenu(Player& player,
    std::vector<Horse>& horse,
    Bank& bank,
    std::vector<Better>& npcs);

  int mainMenu() override;
  void playerMenu() override;
  void betMenu() override;
  void horseMenu() override;
  void bankMenu() override;
  void raceMenu() override;

private:
  Player& player;
  std::vector<Horse>& horse;
  Bank& bank;
  std::vector<Better>& npcs;
};