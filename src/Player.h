//
// Created by melis on 11/5/2025.
//

#ifndef BANKRUPT_PLAYER_H
#define BANKRUPT_PLAYER_H

#include <string>

class Player {
  private:
  std::string name;
  int balance;
  int income;
  int bets;
  int betAmount;
  int betHorseIndex;


  public:
  Player(const std::string& name, int balance, int income);

  int getPaid();
  int checkPay();

  bool placeBet(int amount, int horseIndex);
  void clearBet();


  // Getters/Setters
  std::string getName() const;
  int getBalance() const;
  int getIncome() const;
  int getBets() const;
  int getBetAmount() const;
  int getBetHorseIndex() const;
};

#endif //BANKRUPT_PLAYER_H