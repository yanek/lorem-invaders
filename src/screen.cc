#include "screen.h"

#include "colors.h"
#include "entity.h"
#include "event_bus.h"
#include "screen_title.h"
#include "utils.h"
#include "viewport.h"

#include <algorithm>
#include <cassert>
#include <raylib.h>

Screen *ScreenManager::current_    = nullptr;
Screen *ScreenManager::next_       = nullptr;
EventBus *ScreenManager::eventBus_ = nullptr;
Viewport *ScreenManager::viewport_ = nullptr;

void Screen::addEntity_(Entity *entity)
{
	entities_.push_back(entity);

	if (const auto r = dynamic_cast<RenderedEntity *>(entity))
	{
		renderables_.push_back(r);
		isRenderableListDirty_ = true;
	}

	TraceLog(LOG_DEBUG, "Registered new entity: %s (0x%X)", entity->getName(), entity);
	entity->screen_ = this;
}

void Screen::destroyEntity(Entity *entity)
{
	TraceLog(LOG_DEBUG, "Unregistered entity: %s (0x%X)", entity->getName(), entity);
	entities_.erase(std::remove(entities_.begin(), entities_.end(), entity), entities_.end());

	if (const auto r = dynamic_cast<RenderedEntity *>(entity))
	{
		renderables_.erase(std::remove(renderables_.begin(), renderables_.end(), r), renderables_.end());
		isRenderableListDirty_ = true;
	}

	delete entity;
}

void Screen::clearEntities()
{
	for (auto it = renderables_.begin(); it != renderables_.end();)
	{
		it = renderables_.erase(it);
	}

	uint32_t count = 0;
	for (auto it = entities_.begin(); it != entities_.end();)
	{
		delete *it;
		it = entities_.erase(it);
		++count;
	}

	TraceLog(LOG_DEBUG, "Cleared %d entities", count);
}

void Screen::sortRendered_()
{
	if (!isRenderableListDirty_) return;
	auto cnd = [](const auto a, const auto b) {
		return a->getLayer() < b->getLayer();
	};
	std::sort(renderables_.begin(), renderables_.end(), cnd);
	isRenderableListDirty_ = false;
}

void ScreenManager::init(Viewport *viewport)
{
	viewport_ = viewport;
	eventBus_ = new EventBus{};
	changeToScreen(new TitleScreen{});
}

void ScreenManager::changeToScreen(Screen *newScreen)
{
	assert(next_ == nullptr);
	next_ = newScreen;
}

void ScreenManager::update()
{
	if (next_ != nullptr)
	{
		if (current_ != nullptr)
		{
			TraceLog(LOG_INFO, "Unloading screen %s", current_->getName());
			current_->unload();
			current_->clearEntities();
			delete current_;
		}

		current_ = next_;
		next_    = nullptr;
		current_->init();
		TraceLog(LOG_INFO, "Loading screen %s", current_->getName());
		return;
	}

	float delta = GetFrameTime();
	if (current_->isPaused_) delta = 0.0f;

	for (const auto entity : current_->entities_)
	{
		if (!entity->isActive()) continue;
		entity->update(delta);
	}
	current_->update(delta);

	current_->sortRendered_();

	// Draw to render texture
	viewport_->beginDrawing();
	{
		ClearBackground(color::background);
		for (const auto entity : current_->renderables_)
		{
			if (!entity->isActive()) continue;
			entity->draw(delta);
		}
		current_->draw(delta);
	}
	viewport_->endDrawing();

	// Draw render texture to screen
	BeginDrawing();
	{
		ClearBackground(color::black);
		viewport_->drawRenderTexture();
		drawDebugData();
	}
	EndDrawing();
}

void ScreenManager::close()
{
	current_->unload();
	current_->clearEntities();
	delete current_;
	delete eventBus_;
	current_  = nullptr;
	eventBus_ = nullptr;
}