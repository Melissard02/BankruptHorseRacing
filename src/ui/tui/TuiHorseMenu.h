#pragma once

#include "../../core/Horse.h"
#include "interfaces/IHorseMenu.h"

#include <vector>

class TuiHorseMenu : public IHorseMenu {
public:
  TuiHorseMenu(std::vector<Horse>& horses)
      : horses(horses) {}

  void horseMenu() override;

private:
  int runMainMenu();
  void showHorseList();
  void showAllStats();
  void showSingleHorse(int index);
  void showSingleHorsePrompt();

  std::vector<Horse>& horses;
};
