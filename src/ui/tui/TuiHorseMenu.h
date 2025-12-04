#pragma once

#include "../../core/Horse.h"
#include "interfaces/IHorseMenu.h"
#include <ftxui/component/screen_interactive.hpp>

class TuiHorseMenu : public IHorseMenu {
public:
  TuiHorseMenu(ftxui::ScreenInteractive& screen,
               std::vector<Horse>& horses);

  void horseMenu() override;

private:
  void showHorseList();
  void showSingleHorsePrompt();
  void showSingleHorse(int index);

  ftxui::ScreenInteractive& screen;
  std::vector<Horse>& horses;
};
