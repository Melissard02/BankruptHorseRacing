#pragma once

#include "../../core/Player.h"
#include "../../core/Horse.h"
#include "../../core/Better.h"
#include <vector>
#include <string>

class RaceAnimation {
public:
  RaceAnimation(Player& player,
                   std::vector<Horse>& horses,
                   std::vector<Better>& npcs,
                   bool legendarySpawned,
                   const std::string& legendaryName)
      : player(player),
        horses(horses),
        npcs(npcs),
        legendarySpawned(legendarySpawned),
        legendaryName(legendaryName) {}

  void runRace();

private:
  void runCountdown();
  void simulateRace(std::vector<int>& placements);
  void showWinnerScreen(const std::vector<int>& placements);

  Player& player;
  std::vector<Horse>& horses;
  std::vector<Better>& npcs;

  bool legendarySpawned;
  std::string legendaryName;

  const int raceLength = 100;  // same as your original logic
};
