#pragma once

class Shake;

class Player
{
public:
	void Update(float delta);
	void DrawHud() const;
	void Damage();
	bool IsDead() const;
	void IncrementScore(unsigned long value);

private:
	unsigned long mScore{ 0 };
	unsigned char mHitpoints{ 3 };
	unsigned char mMaxHitpoints{ 3 };
	Shake *mShake{ nullptr };
};
