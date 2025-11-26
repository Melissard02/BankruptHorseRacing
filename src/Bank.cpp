//
// Created by melis on 11/25/2025.
//

#include "Bank.h"

#include <iostream>
Bank::Bank(const Player& player) {
  savings = 1000;
  checking = player.getBalance();
 }

 Bank::Bank(int startSavings, int startChecking) {
  savings = startSavings;
  checking = startChecking;
 }

void Bank::Deposit(int amount, bool toSavings) {
  if (amount <= 0) return;

  if (toSavings) {
   savings += amount;
   checking -= amount;
  }
  else {
   std::cout << "Who do you think you are? Where is this money coming from?\n";
  }
 }

void Bank::Withdraw(int amount, bool fromSavings) {
  if (amount <= 0) return;
  if (fromSavings) {
   if (savings >= amount) {
    savings -= amount;
    checking += amount;
   }
  }
  else {
   if (checking >= amount) {
    std::cout << "And just where are you supposed to put this money?\n";
   }
  }
 }


