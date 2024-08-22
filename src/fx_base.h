#pragma once

class FxBase
{
public:
	virtual ~FxBase() = default;
	virtual void Update(float delta) = 0;
	bool ShouldDie() const;

protected:
	explicit FxBase(int durationMilliseconds);
	float mDuration = 0;
	float mElapsed = 0;
};