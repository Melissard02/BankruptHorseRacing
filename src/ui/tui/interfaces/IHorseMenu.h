#pragma once

class IHorseMenu {
public:
  virtual ~IHorseMenu() = default;

  virtual void horseMenu() = 0;
};
