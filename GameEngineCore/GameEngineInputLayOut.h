#pragma once
#include <d3d11.h>

class GameEngineInputLayout
{
private:
	ID3D11InputLayout* Layout = nullptr;

	void ResCreate();
	void Setting();
protected:
public:

#pragma region Constructor
	GameEngineInputLayout() {}
	~GameEngineInputLayout();
	GameEngineInputLayout(const GameEngineInputLayout&) = delete;
	GameEngineInputLayout(GameEngineInputLayout&&) noexcept = delete;
	GameEngineInputLayout& operator=(const GameEngineInputLayout&) = delete;
	GameEngineInputLayout& operator=(GameEngineInputLayout&&) noexcept = delete;
#pragma endregion
};