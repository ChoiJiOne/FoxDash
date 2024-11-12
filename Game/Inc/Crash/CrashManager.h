#pragma once

#include <functional>
#include <string>

#include "Utils/Macro.h"

/**
 * 어플레케이션의 크래시 처리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class CrashManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(CrashManager);

	/** 크래시 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static CrashManager& GetRef();

	/** 크래시 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static CrashManager* GetPtr();

private:
	/** GameApp에서 크래시 매니저의 내부에 접근할 수 있도록 설정.  */
	friend class GameApp;

	/**
	 * 크래시 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	CrashManager() = default;
	virtual ~CrashManager() {}

	/** 크래시 매니저의 초기화 및 해제는 GameApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

private:
	/** 크래시 매니저의 싱글턴 객체입니다. */
	static CrashManager instance_;
};
