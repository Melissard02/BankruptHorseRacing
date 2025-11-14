//
// Created by melis on 11/5/2025.
//

#ifndef BANKRUPT_RACE_H
#define BANKRUPT_RACE_H

#include "Horse.h"
#include <vector>

class Race {
private:
  std::vector<Horse> horses;
  std::vector<int> progress;
  int winnerIndex;

public:
  Race(const std::vector<Horse>& horses);

  void startRace();
  int getWinnerIndex() const;
};

#endif //BANKRUPT_RACE_H