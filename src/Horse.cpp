//
// Created by melis on 11/5/2025.
//

#include "Horse.h"
#include "Utils.h"
#include <iostream>

 Horse::Horse(const std::string& name, bool legendary)
   : name(name), speed(0), stamina(0), popularity(0), luck(0), wins(0), races(0), legendary(legendary) {}

void Horse::generateStats() {
   if (legendary) {
     if (name == "Seabiscuit") {
       speed = 90; stamina = 90; popularity = 8; luck = 5;
     } else if (name == "Shadowfax") {
       speed = 100; stamina = 90; popularity = 10; luck = 7;
     } else if (name == "Spirit") {
       speed = 80; stamina = 90; popularity = 10; luck = 6;
     } else if (name == "Twilight Sparkle") {
       speed = 99; stamina = 70; popularity = 9; luck = 7;
     } else if (name == "Epona") {
       speed = 70; stamina = 100; popularity = 9; luck = 5;
     } else if (name == "Potoooooooo") {
       speed = 80; stamina = 80; popularity = 8; luck = 5;
     } else if (name == "Spamton G. Spamton") {
       speed = 50; stamina = 50; popularity = 1; luck = 0;
     }
   }
   speed = getRandom(50, 100);
   stamina = getRandom(50, 100);
   popularity = getRandom(1, 10);
   luck = getRandom(0, 5);
 }

void Horse::addRaceResult(bool won) {
   races ++;
   if (won) {
     wins++;
   }
 }

float Horse::winRate() const {
   if (races == 0) return 0.0f;
   return static_cast<float>(wins) / races;
 }

void Horse::displayStats() const {
   std::cout << "Horse: " << name << "\n";
   std::cout << "Speed: " << speed << "\n";
   std::cout << "Stamina: " << stamina << "\n";
   std::cout << "Popularity: " << popularity << "\n";
   // Luck will be a hidden stat
   std::cout << "Luck: " << luck << "\n";
   std::cout << "Wins: " << wins << "/" << races
   << " (Win Rate: " << winRate() * 100 << "%)\n\n";
 }

std::string Horse::getName() const { return name; }
int Horse::getSpeed() const { return speed; }
int Horse::getStamina() const { return stamina; }
int Horse::getPopularity() const { return popularity; }
int Horse::getLuck() const { return luck; }
int Horse::getWins() const { return wins; }
int Horse::getRaces() const { return races; }
bool Horse::isLegendary() const { return legendary; }
