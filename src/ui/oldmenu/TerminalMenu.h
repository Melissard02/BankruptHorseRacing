// # pragma once
//
// #include "Menu.h"
// #include "../../core/Player.h"
// #include "../../core/Horse.h"
// #include "../../core/Better.h"
// #include "../../core/Bank.h"
// #include "../../core/Race.h"
// #include "../../core/Utils.h"
//
// #include <vector>
//
// class TerminalMenu : public UI {
// public:
//   TerminalMenu(
//     // Race& race,
//     Player& player,
//     std::vector<Horse>& horses,
//     Bank& bank,
//     std::vector<Better>& npcs,
//     bool& legendarySpawned,
//     std::string& legendaryName
//     );
//
//   int mainMenu() override;
//   void playerMenu() override;
//   void betMenu() override;
//   void horseMenu() override;
//   void bankMenu() override;
//   void raceMenu() override;
//
// private:
//   // Race& race;
//   Player& player;
//   std::vector<Horse>& horses;
//   Bank& bank;
//   std::vector<Better>& npcs;
//   bool& legendarySpawned;
//   std::string& legendaryName;
//
//   Menu menu;
// };