//
// Created by melis on 11/5/2025.
//

#include "Player.h"
#include <iostream>

// This class handles logic not in/out

 Player::Player(const std::string &name, int balance, int income)
  : name(name), balance(balance), income(income), bets(0) {}

bool Player::placeBet(int amount, int horseIndex) {
   if (amount > balance) {
     std::cout << "You don't have enough funds.\n";
     return false;
   }
   if (amount <= 49) {
     std::cout << "Bet must be at least $50";
     return false;
   }
   balance -= amount;
   betAmount = amount;
   betHorseIndex = horseIndex;
   return true;
 }

void Player::clearBets() {
   betAmount = 0;
   betHorseIndex = -1;
 }

void Player::addMoney(int amount) {
   balance += amount;
 }

void Player::subtractMoney(int amount) {
   balance -= amount;
 }

std::string Player::getName() const{ return name; }
int Player::getBalance() const{ return balance; }
int Player::getIncome() const{ return income; }
int Player::getBets() const{ return bets; }
int Player::getBetHorseIndex() const{ return betHorseIndex; }
int Player::getBetAmount() const{ return betAmount; }
