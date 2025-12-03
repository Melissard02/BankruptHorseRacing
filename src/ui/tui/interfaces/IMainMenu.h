#pragma once

class IMainMenu {
public:
  virtual ~IMainMenu() = default;

  // Returns the player choice (like before)
  virtual int mainMenu() = 0;
};
