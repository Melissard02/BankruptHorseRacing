#include "Database.h"
#include <iostream>

int main() {
  Database db;

  GameSave save;
  save.playerName = "Melissa";
  save.balance = 500;
  save.income = 100;
  save.bets = 0;
  save.betAmount = 0;
  save.betHorseIndex = -1;

  HorseSave h;
  h.horseName = "Zoomy";
  h.legendary = true;
  h.speed = 9; h.stamina = 7; h.popularity = 5; h.luck = 8;
  h.wins = 3; h.races = 5;
  save.horses.push_back(h);

  if (!db.saveGame(save)) {
    std::cout << "Save failed\n";
    return 1;
  }

  GameSave loaded;
  if (!db.loadGame("Melissa", loaded)) {
    std::cout << "Load failed\n";
    return 1;
  }

  std::cout << "Loaded: " << loaded.playerName
            << " balance=" << loaded.balance
            << " horses=" << loaded.horses.size() << "\n";
}
