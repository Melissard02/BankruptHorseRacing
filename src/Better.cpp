#include "Better.h"
#include "Utils.h"

Better::Better(const std::string& name, int balance)
    : Player(name, balance, 0) {}

int Better::makeRandomBet(int minBet, int maxBet) {
  int amount = getRandom(minBet, maxBet);
  placeBet(amount);
  return amount;
}

int Better::chooseRandomHorse(int totalHorses) {
  return getRandom(0, totalHorses - 1);
}
