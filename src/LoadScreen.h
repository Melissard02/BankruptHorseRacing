#ifndef BANKRUPT_LOADSCREEN_H
#define BANKRUPT_LOADSCREEN_H
#include <string>
#include "GameSave.h"
#include "Database.h"

class LoadScreen {
public:
  static int loadScreen();
  static std::string newGame();
  static bool loadGame();
  // void settings();

  const GameSave& getSave() const { return gsave; }

private:
  static void clearScreen();

  Database database;
  GameSave gsave;
};

#endif // BANKRUPT_LOADSCREEN_H
