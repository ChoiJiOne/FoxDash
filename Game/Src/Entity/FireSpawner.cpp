#include <glm/gtc/constants.hpp>

#include "Entity/EntityManager.h"
#include "Entity/Fire.h"
#include "Entity/FireSpawner.h"
#include "Entity/Playground.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Scene/GamePlayScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Math.h"

FireSpawner::FireSpawner(const glm::vec2& position)
{
	tickOrder_ = 5;
	renderOrder_ = 1;

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	playground_ = EntityManager::GetRef().GetByName<Playground>("Playground");
	gamePlayScene_ = SceneManager::GetRef().GetByName<GamePlayScene>("GamePlayScene");

	renderBound_ = Rect2D(position, glm::vec2(64.0f, 128.0f));
	collisionBound_ = renderBound_;
	collisionBound_.size.y *= 0.5f;

	shadow_.scale = 0.5f;
	shadow_.bound = renderBound_;
	shadow_.bound.size.y *= shadow_.scale;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
	shadow_.option.blend = glm::vec3(0.0f, 0.0f, 0.0f);
	shadow_.option.factor = 1.0f;
	shadow_.option.transparent = 0.3f;
	shadow_.option.bIsFlipV = true;

	std::vector<std::string> burnClipNames =
	{
		"Burning_1",
		"Burning_2",
		"Burning_3",
		"Burning_4",
		"Burning_5",
		"Burning_6",
		"Burning_7",
		"Burning_8",
	};
	animator_ = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas_, burnClipNames, 1.0f, true);

	waitTime_ = 0.0f;
	maxWaitTime_ = 2.0f;
	minFireSpeed_ = 100.0f;
	maxFireSpeed_ = 400.0f;

	bIsInitialized_ = true;
}

FireSpawner::~FireSpawner()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void FireSpawner::Tick(float deltaSeconds)
{
	animator_->Update(deltaSeconds);

	switch (state_)
	{
	case EState::WAIT:
	{
		waitTime_ += deltaSeconds;
		if (waitTime_ >= maxWaitTime_)
		{
			waitTime_ -= maxWaitTime_;
			state_ = EState::GENERATE;
		}
	}
	break;

	case EState::GENERATE:
	{
		glm::vec2 postiton = renderBound_.center;
		glm::vec2 direction = GenerateRandomVec2(-postiton, glm::pi<float>() / 2.0f);
		float speed = GenerateRandomFloat(minFireSpeed_, maxFireSpeed_);

		Fire* fire = EntityManager::GetRef().Create<Fire>(postiton, direction, speed);
		fires_.push_back(fire);

		gamePlayScene_->AddUpdateEntity(fire);
		gamePlayScene_->AddRenderEntity(fire);

		state_ = EState::WAIT;
	}
	break;
	}

	for (auto& fire : fires_)
	{
		if (fire && fire->GetState() == Fire::EState::DONE)
		{
			gamePlayScene_->RemoveUpdateEntity(fire);
			gamePlayScene_->RemoveRenderEntity(fire);
			EntityManager::GetRef().Destroy(fire);
			fire = nullptr;
		}
	}

	fires_.remove_if([&](Fire* fire) { return fire == nullptr; });
}

void FireSpawner::Render()
{
	TextureAtlas2D* animationTexture = animator_->GetTextureAtlas();
	const std::string& animationClipName = animator_->GetCurrentClipName();

	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);
	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, shadow_.bound.center, shadow_.bound.size.x, shadow_.bound.size.y, 0.0f, shadow_.option);
}

void FireSpawner::Release()
{
	CHECK(bIsInitialized_);

	if (animator_)
	{
		GLManager::GetRef().Destroy(animator_);
		animator_ = nullptr;
	}

	playground_ = nullptr;
	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}