#pragma once

class Player
{
public:
	void Damage();
	bool IsDead() const;
	void DrawHud() const;
	void IncrementScore(unsigned long value);

private:
	unsigned long score{ 0 };
	unsigned char hitpoints{ 3 };
	unsigned char maxHitpoints{ 3 };
};
