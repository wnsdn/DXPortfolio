#include "PreCompile.h"
#include "GameEngineDirectBuffer.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11")

GameEngineDirectBuffer::~GameEngineDirectBuffer()
{
	if (Buffer)
	{
		Buffer->release();
		Buffer = nullptr;
	}
}
