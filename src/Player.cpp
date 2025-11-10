//
// Created by melis on 11/5/2025.
//

#include "Player.h"
#include <iostream>

// This class handles logic not in/out

 Player::Player(const std::string &name, int balance, int income)
  : name(name), balance(balance), income(income), bets(0), betAmount(0), betHorseIndex(-1) {}

bool Player::placeBet(int amount, int horseIndex) {
   if (amount > balance || amount < 50) {
     std::cout << "You don't have enough funds. Minimum bet of $50\n";
     return false;
   }
   balance -= amount;
   betAmount = amount;
   betHorseIndex = horseIndex;
   bets += 1;
   return true;
 }

void Player::clearBet() {
   betAmount = 0;
   betHorseIndex = -1;
 }


std::string Player::getName() const{ return name; }
int Player::getBalance() const{ return balance; }
int Player::getIncome() const{ return income; }
int Player::getBets() const{ return bets; }
int Player::getBetHorseIndex() const{ return betHorseIndex; }
int Player::getBetAmount() const{ return betAmount; }
