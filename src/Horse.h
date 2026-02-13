//
// Created by melis on 11/5/2025.
//

#ifndef BANKRUPT_HORSE_H
#define BANKRUPT_HORSE_H

#include <string>

class Horse {
private:
  bool legendary;
  std::string name;
  int speed;
  int stamina;
  int popularity;
  int luck;

  int wins = 0;
  int races = 0;

  public:
  Horse(const std::string& name, bool legendary = false);
  bool isLegendary() const;

  void appendMedal(const std::string& medal);
  void clearMedal();

  void addWin() { wins++; }


  void generateStats();
  void addRaceResult(bool won);
  float winRate() const;
  void displayStats() const;

  std::string getName() const;
  int getSpeed() const;
  int getStamina() const;
  int getPopularity() const;
  int getLuck() const;
  int getWins() const;
  int getRaces() const;

  void setLoadedData(int speed_, int stamina_, int popularity_, int luck_, int wins_, int races_) {
    speed = speed_;
    stamina = stamina_;
    popularity = popularity_;
    luck = luck_;
    wins = wins_;
    races = races_;
  }

};

#endif //BANKRUPT_HORSE_H