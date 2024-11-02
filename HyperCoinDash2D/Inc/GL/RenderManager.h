#pragma once

#include <array>
#include <map>
#include <queue>

#include <glm/glm.hpp>

#include "Macro.h"

/**
 * 2D 렌더링을 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class RenderManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager);

	/** 렌더 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static RenderManager& GetRef();

	/** 렌더 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static RenderManager* GetPtr();

private:
	/** GameApp에서 렌더 매니저의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/**
	 * 렌더 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	RenderManager() = default;
	virtual ~RenderManager() {}

	/** 렌더 매니저의 초기화 및 해제는 GameApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();
	
private:
	/** 렌더 매니저의 싱글턴 객체입니다. */
	static RenderManager singleton_;

	/** 렌더 매니저 내부에서 사용할 GL 매니저입니다. */
	class GLManager* glManager_ = nullptr;
};