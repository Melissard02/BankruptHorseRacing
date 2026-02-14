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
  Bank() = default;
  explicit Bank(int startSavings);

  void transfer(Player& player, int amount, bool fromSavings);

  int getSavings() const { return savings; };
  void setSavings(int s) {savings = s;};

};

#endif // BANKRUPT_BANK_H
