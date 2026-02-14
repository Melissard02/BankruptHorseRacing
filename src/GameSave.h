
#ifndef BANKRUPT_GAMESAVE_H
#define BANKRUPT_GAMESAVE_H

#include <string>
#include <vector>

struct HorseSave {
  std::string horseName;
  bool legendary = false;

  int speed = 0;
  int stamina = 0;
  int popularity = 0;
  int luck = 0;

  int wins = 0;
  int races = 0;

  double winRate() const {
  return (races == 0) ? 0.0 : (double)wins / races;
  }
};

struct GameSave {
  std::string playerName;
  int balance = 0;
  int savings = 0;
  int income = 0;
  int bets = 0;
  int betAmount = 0;
  int betHorseIndex = -1;

  std::vector<HorseSave> horses;
};



#endif // BANKRUPT_GAMESAVE_H
