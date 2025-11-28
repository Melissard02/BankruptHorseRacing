#pragma once

class UI {
  public:
  virtual int mainMenu() = 0;
  virtual void playerMenu() = 0;
  virtual void betMenu() = 0;
  virtual void horseMenu() = 0;
  virtual void bankMenu() = 0;
  virtual void raceMenu() = 0;

  virtual ~UI() {}

};