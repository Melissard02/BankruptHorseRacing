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

  void placeBet(int amount);
  void addMoney(int amount);
  void subtractMoney(int amount);
  bool placeBet(int amount, int horseIndex);
  void clearBets();

  // Getters/Setters
  std::string getName() const;
  int getBalance() const;
  int getIncome() const;
  int getBets() const;
  int getBetHorseIndex() const;
  int getBetAmount() const;

};

#endif //BANKRUPT_PLAYER_H