#include <glm/gtc/random.hpp>

#include "Entity/Coin.h"
#include "Entity/CoinSpawner.h"
#include "Entity/EntityManager.h"
#include "Scene/GamePlayScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

CoinSpawner::CoinSpawner()
{
	tickOrder_ = 5;
	renderOrder_ = 1;

	bound_ = Circle2D(glm::vec2(0.0f, 0.0f), 1000.0f);
	countCoin_ = 20;
	for (uint32_t count = 0; count < countCoin_; ++count)
	{
		glm::vec2 position = glm::diskRand(bound_.radius);
		Coin* coin = EntityManager::GetRef().Create<Coin>(position);
		coins_.push_back(coin);

		GamePlayScene* gamePlayScene = SceneManager::GetRef().GetByName<GamePlayScene>("GamePlayScene");
		gamePlayScene->AddUpdateEntity(coin);
		gamePlayScene->AddRenderEntity(coin);
	}

	bIsInitialized_ = true;
}

CoinSpawner::~CoinSpawner()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void CoinSpawner::Tick(float deltaSeconds)
{

}

void CoinSpawner::Render()
{
	renderManager_->DrawCircleWireframe(bound_.center, bound_.radius, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void CoinSpawner::Release()
{
	CHECK(bIsInitialized_);
	
	bIsInitialized_ = false;
}
