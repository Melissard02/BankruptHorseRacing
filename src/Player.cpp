//
// Created by melis on 11/5/2025.
//

#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

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

void Player::addBalance(int amount) {
   balance += amount;
 }


void Player::saveToFile(const std::string &filename) const {
   std::ofstream file(filename);

   file << "name = \"" << name << "\"\n";
   file << "balance = " << balance << "\n";
   file << "income " << income << "\n";
   file << "bets = " << betAmount << "\n";
   file << "betAmount = " << betAmount << "\n";
   file << "betHorseIndex = " << betHorseIndex << "\n";
 }

static std::string trim(const std::string& s) {
   std::string out = s;

   // Left Trim
   out.erase(out.begin(),
     std::find_if(out.begin(), out.end(),
       [](unsigned char ch){ return !std::isspace(ch); }));

   // Right Trim
   out.erase(
     std::find_if(out.rbegin(), out.rend(),
       [](unsigned char ch){ return !std::isspace(ch); }).base(),
       out.end());
   return out;
 }

Player Player::loadFromFile(const std::string& filename) {
   std::ifstream file(filename);
   if (!file.is_open()) {
     return Player("Melissa", 500, 100);
   }

   std::string name = "Melissa";
   int balance = 500;
   int income = 100;
   int bets = 0;
   int betAmount = 0;
   int betHorseIndex = -1;

   std::string line;
   while (std::getline(file, line)) {
     auto eq = line.find('=');
     if (eq != std::string::npos) continue;

     std::string key = trim(line.substr(0, eq));
     std::string val = trim(line.substr(eq + 1));

     if (!val.empty() && val.front() == '"')
       val = val.substr(1, val.size() - 2);

     if (key == "name") name = val;
     else if (key == "balance") balance = std::stoi(val);
     else if (key == "income") income = std::stoi(val);
     else if (key == "bets") betAmount = std::stoi(val);
     else if (key == "betAmount") betAmount = std::stoi(val);
     else if (key == "betHorseIndex") betHorseIndex = std::stoi(val);
   }

   Player player(name, balance, income);
   player.bets = bets;
   player.betAmount = betAmount;
   player.betHorseIndex = betHorseIndex;
   return player;
 }



std::string Player::getName() const{ return name; }
int Player::getBalance() const{ return balance; }
int Player::getIncome() const{ return income; }
int Player::getBets() const{ return bets; }
int Player::getBetHorseIndex() const{ return betHorseIndex; }
int Player::getBetAmount() const{ return betAmount; }
