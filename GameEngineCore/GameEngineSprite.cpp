#include "PreCompile.h"
#include "GameEngineSprite.h"

float4 SpriteData::GetScale()
{
	return Texture->GetScale() * float4(Pivot.Scale2DX, Pivot.Scale2DY, 1.0f, 0.0f);
}

void GameEngineSprite::ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
{
	auto Texture = GameEngineTexture::Find(_Name);

	SpriteDatas.resize(_X * _Y);

	float4 Start;
	Start.Pos2DX = 0.0f;
	Start.Pos2DY = 0.0f;
	Start.Scale2DX = 1.0f / _X;
	Start.Scale2DY = 1.0f / _Y;

	for (size_t y = 0; y < _Y; ++y)
	{
		for (size_t x = 0; x < _X; ++x)
		{
			auto Index = (y * _X) + x;
			SpriteDatas[Index].Texture = Texture;

			SpriteDatas[Index].Pivot = Start;
			Start.Pos2DX += Start.Scale2DX;
		}

		Start.Pos2DX = 0.0f;
		Start.Pos2DY += Start.Scale2DY;
	}
}

void GameEngineSprite::ResCreateFolder(std::string_view _Path)
{
	GameEngineDirectory Dir;
	Dir.SetPath(_Path);

	auto AllPath = Dir.GetAllFileInDir();

	SpriteDatas.resize(AllPath.size());

	for (int i = 0; i < AllPath.size(); ++i)
	{
		SpriteDatas[i].Texture = GameEngineTexture::Load(AllPath[i].GetPath());
		SpriteDatas[i].Pivot = float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
}

SpriteData GameEngineSprite::GetSpriteData(unsigned int _Index)
{
	if (_Index >= SpriteDatas.size())
	{
		assert(false);
		return SpriteData();
	}

	return SpriteDatas[_Index];
}
