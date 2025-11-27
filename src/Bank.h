//
// Created by melis on 11/25/2025.
//

#ifndef BANKRUPT_BANK_H
#define BANKRUPT_BANK_H
#include "Player.h"

class Bank {
  private:
  int savings;

  public:
  Bank(const Player& player);
  Bank(int startSavings, int startChecking);

  void Transfer(Player& player, int amount, bool fromSavings);

  int getSavings() const { return savings; };

};

#endif // BANKRUPT_BANK_H
