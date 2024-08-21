#include "entity.h"
#include "colors.h"
#include "inputbox.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>
#include <vector>

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
	entity.velocity = Vector2{ 0, 100 };
	entity.value = value;
	entity.active = true;

	return id;
}

Enemy &EnemyPool::Get(const size_t id)
{
	return this->pool[id];
}

size_t EnemyPool::Count() const
{
	return this->pool.size();
}

void EnemyPool::UpdateAll(const GameScreen *screen, const float delta)
{
	for (auto &entity : this->pool)
	{
		if (entity.active)
		{
			entity.Update(screen, delta);
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

void Enemy::Despawn()
{
	this->active = false;
	this->highlightOffset = 0;
	this->position = Vector2{ 0, 0 };
	this->velocity = Vector2{ 0, 0 };
}

void Enemy::Draw() const
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	DrawTextEx(res::font16, this->value.c_str(), this->position, fntsize, 0, color::white);
	DrawTextEx(res::font16, this->value.substr(0, this->highlightOffset).c_str(), this->position, fntsize, 0, color::red);
}

void Enemy::Update(const GameScreen *screen, const float delta)
{
	InputBox *inputBox = screen->GetInputBox();
	Player *player = screen->GetPlayer();

	this->position.x += this->velocity.x * delta;
	this->position.y += this->velocity.y * delta;

	const int matchval = inputBox->GetMatch(this->value);
	this->highlightOffset = matchval;

	if (matchval >= this->value.length())
	{
		inputBox->Clear();
		player->IncrementScore(this->value.length());
		Despawn();
	}

	if (this->position.y > Viewport::gameHeight - 32)
	{
		player->Damage();
		Despawn();
	}
}