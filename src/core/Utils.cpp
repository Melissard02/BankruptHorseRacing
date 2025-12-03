//
// Created by melis on 11/5/2025.
//

#include "./Utils.h"
#include <random>

int getRandom(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution dist(min, max);
  return dist(gen);
}

