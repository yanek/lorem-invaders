#pragma once

class Player {
public:
  void Damage();
  bool IsDead() const;
  void DrawHud() const;

private:
  int hitpoints{3};
  int maxHitpoints{3};
};
