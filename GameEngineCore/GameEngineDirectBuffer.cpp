#include "PreCompile.h"
#include "GameEngineDirectBuffer.h"

GameEngineDirectBuffer::~GameEngineDirectBuffer()
{
	SafeRelease(Buffer);
}
