#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class SpriteAnimator2D;
class TextureAtlas2D;

/** 플레이어가 조종할 엔티티입니다. */
class Player : public IEntity2D
{
public:
	Player();
	virtual ~Player();

	DISALLOW_COPY_AND_ASSIGN(Player);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 플레이어의 중심 위치를 얻습니다. */
	const glm::vec2 GetPosition() const;

	/** 플레이어의 경계 충돌 영역을 얻습니다. */
	const Circle2D* GetCollider() const { return &collisionBound_; }

private:
	/** 플레이어의 애니메이션 상태입니다. */
	enum class EAnimationState
	{
		IDLE = 0x00,
		RUN  = 0x01,
		HURT = 0x02,
	};

	/** 플레이어의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

	/** 플레이어의 애니메이션 상태를 초기화합니다. */
	void LoadAnimations();

	/** 플레이어의 애니메이션 상태 초기화를 해제합니다. */
	void UnloadAnimation();

private:
	/** 플레이어 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 렌더링 영역입니다 */
	Rect2D renderBound_;

	/** 플레이어의 렌더링 옵션입니다. */
	TextureDrawOption renderOption_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 플레이어의 그림자입니다. */
	Shadow shadow_;

	/** 플레이어의 이동 방향입니다. */
	glm::vec2 direction_;
	
	/** 플레이어의 속도입니다. */
	float speed_ = 0.0f;
	
	/** 현재 애니메이션의 상태입니다. */
	EAnimationState animationState_ = EAnimationState::IDLE;

	/** 플레이어의 애니메이션 상태 별 애니메이션 리소스입니다. */
	std::map<EAnimationState, SpriteAnimator2D*> animations_;
};
