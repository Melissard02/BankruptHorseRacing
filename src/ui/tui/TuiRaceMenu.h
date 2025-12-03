#pragma once

#include "interfaces/IRaceMenu.h"
#include "../../core/Horse.h"
#include "../../core/Player.h"
#include "../../core/Better.h"

#include <vector>
#include <string>

class TuiRaceMenu : public IRaceMenu {
public:
  TuiRaceMenu(Player& player,
              std::vector<Horse>& horses,
              std::vector<Better>& npcs,
              bool legendarySpawned,
              const std::string& legendaryName)
      : player(player),
        horses(horses),
        npcs(npcs),
        legendarySpawned(legendarySpawned),
        legendaryName(legendaryName) {}

  void raceMenu() override;

private:
  int runMainMenu();
  void showHorsesScreen();

  Player& player;
  std::vector<Horse>& horses;
  std::vector<Better>& npcs;

  bool legendarySpawned;
  std::string legendaryName;
};
