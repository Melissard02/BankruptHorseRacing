#pragma once

#include "../../core/Player.h"
#include "../../core/Horse.h"
#include "../../core/Better.h"

#include "interfaces/IRaceMenu.h"
#include <ftxui/component/screen_interactive.hpp>

class TuiRaceMenu : public IRaceMenu {
public:
  TuiRaceMenu(ftxui::ScreenInteractive& screen,
              Player& player,
              std::vector<Horse>& horses,
              std::vector<Better>& npcs,
              bool legendarySpawned,
              const std::string& legendaryName);

  void raceMenu() override;

private:
  ftxui::ScreenInteractive& screen;
  Player& player;
  std::vector<Horse>& horses;
  std::vector<Better>& npcs;
  bool legendarySpawned;
  std::string legendaryName;
};
