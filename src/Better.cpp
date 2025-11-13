#include "Better.h"
#include "Utils.h"

Better::Better(const std::string& name, int balance)
    : Player(name, balance, 0) {}

int Better::makeRandomBet(int minBet, int maxBet) {
  if (getBalance() < minBet) {
    return 0;
  }
  int amount = getRandom(minBet, std::min(maxBet, getBalance()));
  placeBet(amount, 0);
  return amount;
}

int Better::chooseRandomHorse(int totalHorses) {
  return getRandom(0, totalHorses - 1);
}
