//
// Created by melis on 11/7/2025.
//

#ifndef BANKRUPT_MENU_H
#define BANKRUPT_MENU_H

class Player;
class Horse;
class Race;
#include "Better.h";
#include <vector>

class Menu {
  public:
  int mainMenu() const;
  void playerMenu(const Player& player, const std::vector<Horse> &horses) const;
  void betMenu(Player& player, const std::vector<Horse>& horses) const;
  void horseMenu(const std::vector<Horse>& horses) const;
  void bankMenu(const Player& player) const;
  void raceMenu(Race &race, const std::vector<Horse>& horses,
              Player &player, std::vector<Better>& npcs,
              bool legendarySpawned, const std::string& legendaryName) const;



  private:
  void clearScreen() const;
};
#endif // BANKRUPT_MENU_H
