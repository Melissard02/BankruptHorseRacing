//
// Created by melis on 11/25/2025.
//

#ifndef BANKRUPT_BANK_H
#define BANKRUPT_BANK_H
#include "Player.h"

class Bank {
  private:
  int savings;
  int checking;

  public:
  Bank(const Player& player);
  Bank(int startSavings, int startChecking);

  void Deposit(int amount, bool toSavings);
  void Withdraw(int amount, bool fromSavings);

  int getSavings() const { return savings; };
  int getChecking() const { return checking; };


};

#endif // BANKRUPT_BANK_H
