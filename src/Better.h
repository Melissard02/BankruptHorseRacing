//
// Created by melis on 11/5/2025.
//

#ifndef BANKRUPT_BETTER_H
#define BANKRUPT_BETTER_H
#include "Player.h"
#include <vector>

class Better : public Player {
  public:
    Better(const std::string& name, int balance);

    int makeRandomBet(int minBet, int maxBet);
    int chooseRandomHorse(int totalHorses);
};

#endif //BANKRUPT_BETTER_H