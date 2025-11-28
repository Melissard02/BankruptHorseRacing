//
// Created by melis on 11/25/2025.
//

#include "../Bank.h"

#include <iostream>
Bank::Bank(const Player& player) {
  savings = 1000;
 }

 Bank::Bank(int startSavings, int startChecking) {
  savings = startSavings;
 }

void Bank::Transfer(Player& player, int amount, bool fromSavings) {
  if (amount <= 0) return;

  if (fromSavings) {
   if (savings >= amount) {
    savings -= amount;
    player.addBalance(amount);
   }
  }
  else {
   if (player.getBalance() >= amount) {
    player.addBalance(-amount);
    savings += amount;
   }
  }
}


