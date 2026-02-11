#pragma once

class IPlayerMenu {
public:
  virtual ~IPlayerMenu() = default;
  virtual void playerMenu() = 0;
};
