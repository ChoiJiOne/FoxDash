#pragma once

#include "GLFW/GLFWManager.h"
#include "Utils/Utils.h"

#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * 이 매크로는 GLFW API의 호출 결과 평가식을 검사합니다.
 * ex) 
 * GLFWwindow* window = glfwCreateWindow(...);
 * GLFW_EXP_CHECK(window != nullptr);
 */
#ifndef GLFW_EXP_CHECK
#define GLFW_EXP_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n> Description: %s\n\n", GLFWManager::GetRef().GetErrorCode(),  GLFWManager::GetRef().GetErrorMessage(),  GLFWManager::GetRef().GetErrorDescription());\
		__debugbreak();\
	}\
}
#endif
/**
 * 이 매크로는 GLFW API의 API 호출 결과를 검사합니다. 주로, 반환 값이 없는 API를 대상으로 합니다.
 * ex)
 * GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VERSION));
 */
#ifndef GLFW_API_CHECK
#define GLFW_API_CHECK(EXP)\
{\
	EXP;\
	if (GLFWManager::GetRef().IsDetectError())\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n> Description: %s\n\n", GLFWManager::GetRef().GetErrorCode(),  GLFWManager::GetRef().GetErrorMessage(),  GLFWManager::GetRef().GetErrorDescription());\
		__debugbreak();\
	}\
}
#endif
#else // defined(RELEASE_MODE) || defined(MINSIZEREL_MODE)
/**
 * 이 매크로는 GLFW API의 호출 결과 평가식을 검사합니다.
 * ex)
 * GLFWwindow* window = glfwCreateWindow(...);
 * GLFW_EXP_CHECK(window != nullptr);
 */
#ifndef GLFW_EXP_CHECK
#define GLFW_EXP_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		std::string _text = PrintF("> Code: %d\n> Error: %s\n> Description: %s", GLFWManager::GetRef().GetErrorCode(),  GLFWManager::GetRef().GetErrorMessage(),  GLFWManager::GetRef().GetErrorDescription());\
		CrashManager::GetRef().ShowMessageBox(_text);\
	}\
}
#endif
/**
 * 이 매크로는 GLFW API의 API 호출 결과를 검사합니다. 주로, 반환 값이 없는 API를 대상으로 합니다.
 * ex)
 * GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VERSION));
 */
#ifndef GLFW_API_CHECK
#define GLFW_API_CHECK(EXP)\
{\
	EXP;\
	if (GLFWManager::GetRef().IsDetectError())\
	{\
		std::string _text = PrintF("> Code: %d\n> Error: %s\n> Description: %s", GLFWManager::GetRef().GetErrorCode(),  GLFWManager::GetRef().GetErrorMessage(),  GLFWManager::GetRef().GetErrorDescription());\
		CrashManager::GetRef().ShowMessageBox(_text);\
	}\
}
#endif
#endif