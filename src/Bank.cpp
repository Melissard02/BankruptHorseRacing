//
// Created by melis on 11/25/2025.
//

#include "Bank.h"

Bank::Bank(int startSavings) : savings(startSavings) {}

void Bank::transfer(Player& player, int amount, bool fromSavings) {
 if (amount <= 0) return;

 if (fromSavings) {
  // Move money from savings -> player balance
  if (savings >= amount) {
   savings -= amount;
   player.addBalance(amount);
  }
 } else {
  // Move money from player balance -> savings
  if (player.getBalance() >= amount) {
   player.addBalance(-amount);
   savings += amount;
  }
 }
}
