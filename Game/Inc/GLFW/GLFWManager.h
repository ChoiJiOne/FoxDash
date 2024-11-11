#pragma once

#include <array>
#include <string>

#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "Utils/Macro.h"

/**
 * --------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPress : int32_t
{
	NONE     = 0x00,
	PRESSED  = 0x01,
	RELEASED = 0x02,
	HELD     = 0x03
};

/** 키 코드 값입니다. */
enum class EKey
{
	KEY_SPACE = 32,
	KEY_APOSTROPHE = 39,
	KEY_COMMA = 44,
	KEY_MINUS = 45,
	KEY_PERIOD = 46,
	KEY_SLASH = 47,
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_SEMICOLON = 59,
	KEY_EQUAL = 61,
	KEY_A = 65,
	KEY_B = 66,
	KEY_C = 67,
	KEY_D = 68,
	KEY_E = 69,
	KEY_F = 70,
	KEY_G = 71,
	KEY_H = 72,
	KEY_I = 73,
	KEY_J = 74,
	KEY_K = 75,
	KEY_L = 76,
	KEY_M = 77,
	KEY_N = 78,
	KEY_O = 79,
	KEY_P = 80,
	KEY_Q = 81,
	KEY_R = 82,
	KEY_S = 83,
	KEY_T = 84,
	KEY_U = 85,
	KEY_V = 86,
	KEY_W = 87,
	KEY_X = 88,
	KEY_Y = 89,
	KEY_Z = 90,
	KEY_LEFT_BRACKET = 91,
	KEY_BACKSLASH = 92,
	KEY_RIGHT_BRACKET = 93,
	KEY_GRAVE_ACCENT = 96,
	KEY_WORLD_1 = 161,
	KEY_WORLD_2 = 162,
	KEY_ESCAPE = 256,
	KEY_ENTER = 257,
	KEY_TAB = 258,
	KEY_BACKSPACE = 259,
	KEY_INSERT = 260,
	KEY_DELETE = 261,
	KEY_RIGHT = 262,
	KEY_LEFT = 263,
	KEY_DOWN = 264,
	KEY_UP = 265,
	KEY_PAGE_UP = 266,
	KEY_PAGE_DOWN = 267,
	KEY_HOME = 268,
	KEY_END = 269,
	KEY_CAPS_LOCK = 280,
	KEY_SCROLL_LOCK = 281,
	KEY_NUM_LOCK = 282,
	KEY_PRINT_SCREEN = 283,
	KEY_PAUSE = 284,
	KEY_F1 = 290,
	KEY_F2 = 291,
	KEY_F3 = 292,
	KEY_F4 = 293,
	KEY_F5 = 294,
	KEY_F6 = 295,
	KEY_F7 = 296,
	KEY_F8 = 297,
	KEY_F9 = 298,
	KEY_F10 = 299,
	KEY_F11 = 300,
	KEY_F12 = 301,
	KEY_F13 = 302,
	KEY_F14 = 303,
	KEY_F15 = 304,
	KEY_F16 = 305,
	KEY_F17 = 306,
	KEY_F18 = 307,
	KEY_F19 = 308,
	KEY_F20 = 309,
	KEY_F21 = 310,
	KEY_F22 = 311,
	KEY_F23 = 312,
	KEY_F24 = 313,
	KEY_F25 = 314,
	KEY_KP_0 = 320,
	KEY_KP_1 = 321,
	KEY_KP_2 = 322,
	KEY_KP_3 = 323,
	KEY_KP_4 = 324,
	KEY_KP_5 = 325,
	KEY_KP_6 = 326,
	KEY_KP_7 = 327,
	KEY_KP_8 = 328,
	KEY_KP_9 = 329,
	KEY_KP_DECIMAL = 330,
	KEY_KP_DIVIDE = 331,
	KEY_KP_MULTIPLY = 332,
	KEY_KP_SUBTRACT = 333,
	KEY_KP_ADD = 334,
	KEY_KP_ENTER = 335,
	KEY_KP_EQUAL = 336,
	KEY_LEFT_SHIFT = 340,
	KEY_LEFT_CONTROL = 341,
	KEY_LEFT_ALT = 342,
	KEY_LEFT_SUPER = 343,
	KEY_RIGHT_SHIFT = 344,
	KEY_RIGHT_CONTROL = 345,
	KEY_RIGHT_ALT = 346,
	KEY_RIGHT_SUPER = 347,
	KEY_MENU = 348
};

/**
 * GLFW 관련 처리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class GLFWManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLFWManager);

	/** GLFW 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static GLFWManager& GetRef();
	
	/** GLFW 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static GLFWManager* GetPtr();

	/** 최근에 발생한 GLFW 에러를 설정합니다. */
	void SetLsatError(int32_t code, const char* description);

	/** 에러 발생 여부를 확인합니다. */
	bool IsDetectError() const { return bIsDetectError_; }

	/** GLFW 에러에 대한 코드 값을 얻습니다. */
	const int32_t GetErrorCode() const { return errorCode_; }

	/** GLFW 에러에 대한 설명을 C 스타일 문자열로 얻습니다. */
	const char* GetErrorDescription() const { return errorDescription_.c_str(); }

	/** GLFW 에러에 대한 메시지를 C 스타일 문자열로 얻습니다. */
	const char* GetErrorMessage() const { return errorMessage_.c_str(); }

	/** 한 프레임을 시작합니다. */
	void Tick();

	/** 커서가 윈도우 내부에 있는지 확인합니다. */
	bool IsEnterCursor() const { return bIsEnterCursor_; }

	/** 현재 키 값의 입력 상태를 얻습니다. */
	EPress GetKeyPress(const EKey& key);

	/** Tick 호출 이전의 커서 위치를 얻습니다. */
	const glm::vec2& GetPrevCursorPos() const { return prevCursorPos_; }

	/** Tick 호출 이후의 커서 위치를 얻습니다. */
	const glm::vec2& GetCurrCursorPos() const { return currCursorPos_; }
	
private:
	/** GameApp에서 GLFWManager의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/** GLManager에서 GLFWManager의 내부에 접근할 수 있도록 설정. */
	friend class GLManager;

	/** GLFW 에러 처리를 위한 콜백 함수입니다. */
	static void ErrorCallback(int32_t errorCode, const char* description);

	/** 키보드 입력이 감지되었을 때 호출되는 콜백 함수입니다. */
	static void KeyEventCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);

	/** 마우스 커서가 움직일 때 호출되는 콜백 함수입니다. */
	static void CursorMoveCallback(GLFWwindow* window, double x, double y);

	/** 마우스 커서가 진입했을 때 호출되는 콜백함수입니다. */
	static void CursorEnterCallback(GLFWwindow* window, int32_t entered);

	/** 마우스 버튼 입력이 감지되었을 때 호출되는 콜백 함수입니다. */
	static void MouseButtonEventCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);

	/** 커서의 윈도우 창 진입 여부를 설정합니다. */
	void SetCursorEnter(int32_t entered);

	/** 현재 커서 위치를 설정합니다. */
	void SetCursorPosition(double x, double y);

	/** 현재 키 상태 값을 설정합니다. */
	void SetKeyboardState(int32_t key, int32_t action);

	/**
	 * GLFW 매니저의 기본 생성자와 빈 가상 소멸자입니다. 
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	GLFWManager() = default;
	virtual ~GLFWManager() {}

	/** GLFW 매니저의 초기화 및 해제는 GameApp 내부에서만 수행됩니다. */
	void Startup(int32_t width, int32_t height, const char* title);
	void Shutdown();
	
private:
	/** GLFW 매니저의 싱글턴 객체입니다. */
	static GLFWManager singleton_;

	/** GLFW 매니저가 관리하는 메인 윈도우입니다. */
	GLFWwindow* mainWindow_ = nullptr;

	/** GLFW 매니저가 관리하는 메인 윈도우의 가로/세로 크기입니다. */
	int32_t mainWindowWidth_ = 0;
	int32_t mainWindowHeight_ = 0;

	/** 커서가 윈도우 내부에 있는지 확인합니다. */
	bool bIsEnterCursor_ = true;

	/** Tick 호출 이전의 커서 위치입니다. */
	glm::vec2 prevCursorPos_ = glm::vec2();

	/** Tick 호출 이후의 커서 위치입니다. */
	glm::vec2 currCursorPos_ = glm::vec2();

	/** 키 배열의 최대 값입니다. */
	static const uint32_t KEY_BOARD_STATE_SIZE = 348;

	std::array<int32_t, KEY_BOARD_STATE_SIZE> keyboardState_;

	/** GLFW 에러 발생 여부입니다. */
	bool bIsDetectError_ = false;

	/**
	 * GLFW 에러 코드입니다.
	 * 참조: https://www.glfw.org/docs/3.3/group__errors.html
	 */
	int32_t errorCode_ = 0;

	/** GLFW 에러에 대한 설명 입니다. */
	std::string errorDescription_;

	/** GLFW 에러 메시지입니다. */
	std::string errorMessage_;
};