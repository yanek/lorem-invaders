#include "enemy_pool.h"

#include "resources.h"
#include "viewport.h"

size_t EnemyPool::Spawn(const std::string &value)
{
	const std::vector<Enemy> &pool = mPool;
	size_t id = pool.size();

	TraceLog(LOG_INFO, "Creating enemy: %i", id);

	// Find inactive Entity.
	for (size_t i = 0; i < pool.size(); ++i)
	{
		const Enemy &entity = pool[i];
		if (!entity.mActive)
		{
			id = i;
			break;
		}
	}

	if (id == pool.size())
	{
		mPool.emplace_back();
	}

	// Randomize horizontal position while making sure that the text does not overflow the viewport.
	const float txtsize = MeasureTextEx(res::font16, value.c_str(), res::font16.baseSize, 0).x;
	const float posx = GetRandomValue(0, Viewport::kGameWidth - txtsize);

	Enemy &entity = mPool[id];
	entity.mId = id;
	entity.mPosition = Vector2{ posx, 0.0f };
	entity.mVelocity = Vector2{ 0, 100 };
	entity.mValue = value;
	entity.mActive = true;

	return id;
}

Enemy &EnemyPool::Get(const size_t id)
{
	return mPool[id];
}

size_t EnemyPool::Count() const
{
	return mPool.size();
}

void EnemyPool::UpdateAll(const GameScreen *screen, const float delta)
{
	for (auto &entity : mPool)
	{
		if (entity.mActive)
		{
			entity.Update(screen, delta);
		}
	}
}

void EnemyPool::DrawAll() const
{
	for (const auto &entity : mPool)
	{
		if (entity.mActive)
		{
			entity.Draw();
		}
	}
}