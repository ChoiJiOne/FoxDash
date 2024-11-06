#pragma once

#include <cstdint>

#include "GLResource.h"

/** OpenGL 텍스처 리소스의 인터페이스입니다. */
class ITexture : public GLResource
{
public:
	ITexture() = default;
	virtual ~ITexture() {}

	virtual void Release() = 0;

	/** 텍스처를 렌더링 파이프라인에 바인딩하고 활성화합니다. */
	virtual void Active(uint32_t unit) const = 0;
};