#include "entity.h"
#include "resources.h"
#include "viewport.h"

#include <raylib.h>
#include <vector>

EnemyPool::EnemyPool()
	: pool(std::vector<Enemy>())
{
}

size_t EnemyPool::Spawn(const std::string &value)
{
	const std::vector<Enemy> &pool = this->pool;
	size_t id = pool.size();

	TraceLog(LOG_INFO, "Creating enemy: %i", id);

	// Find inactive Entity.
	for (size_t i = 0; i < pool.size(); ++i)
	{
		const Enemy &entity = pool[i];
		if (!entity.active)
		{
			id = i;
			break;
		}
	}

	if (id == pool.size())
	{
		this->pool.emplace_back();
	}

	// Randomize horizontal position while making sure that the text does not overflow the viewport.
	const float txtsize = MeasureTextEx(res::font16, value.c_str(), res::font16.baseSize, 0).x;
	const float posx = GetRandomValue(0, Viewport::gameWidth - txtsize);

	Enemy &entity = this->pool[id];
	entity.id = id;
	entity.position = Vector2{ posx, 0.0f };
	entity.velocity = Vector2{ 0, 10 };
	entity.value = value;
	entity.active = true;

	return id;
}

void EnemyPool::Despawn(const size_t id)
{
	Enemy &entity = this->pool[id];
	entity.active = false;
}

Enemy &EnemyPool::Get(const size_t id)
{
	return this->pool[id];
}

size_t EnemyPool::Count() const
{
	return this->pool.size();
}

void EnemyPool::UpdateAll()
{
	for (auto &entity : this->pool)
	{
		if (entity.active)
		{
			entity.Update();
		}
	}
}

void EnemyPool::DrawAll() const
{
	for (const auto &entity : this->pool)
	{
		if (entity.active)
		{
			entity.Draw();
		}
	}
}

void Enemy::Draw() const
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	DrawTextEx(res::font16, this->value.c_str(), this->position, fntsize, 0, WHITE);
}

void Enemy::Update()
{
	this->position.x += this->velocity.x * GetFrameTime();
	this->position.y += this->velocity.y * GetFrameTime();
	if (this->position.y > Viewport::gameHeight)
	{
		this->active = false;
	}
}
