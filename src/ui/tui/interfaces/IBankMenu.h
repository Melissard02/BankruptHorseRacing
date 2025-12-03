#pragma once

class IBankMenu {
public:
  virtual ~IBankMenu() = default;
  virtual void bankMenu() = 0;
};
