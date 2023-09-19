#include "PreCompile.h"
#include "GameEngineTilemap.h"

#include "GameEngineTransform.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineCamera.h"

GameEngineTilemap::GameEngineTilemap()
{
}

GameEngineTilemap::~GameEngineTilemap()
{
}

void GameEngineTilemap::CreateTileMap(const CreateTileParameter& _Parameter)
{
	Tiles.resize(_Parameter.TileCountY, std::vector<Tile>(_Parameter.TileCountX));
	DefaultSprite = GameEngineSprite::Find(_Parameter.SpriteName);

	TileData = _Parameter;
	TileData.TileScale.Z = 1.0f;
}

void GameEngineTilemap::SetTilePos(const SetTileParameterPos& _Parameter)
{
	SetTileParameterIndex Parameter;
	Parameter.X = static_cast<size_t>(_Parameter.Pos.X / TileData.TileScale.X);
	Parameter.Y = static_cast<size_t>(_Parameter.Pos.Y / TileData.TileScale.Y);
	Parameter.Index = _Parameter.Index;
	Parameter.SpriteName = _Parameter.SpriteName;

	SetTileIndex(Parameter);
}

void GameEngineTilemap::SetTileIndex(const SetTileParameterIndex& _Parameter)
{
	if (Tiles.size() <= _Parameter.Y)
	{
		assert(false);
	}
	if (Tiles[_Parameter.Y].size() <= _Parameter.X)
	{
		assert(false);
	}

	Tile& CurTile = Tiles[_Parameter.Y][_Parameter.X];

	if (_Parameter.SpriteName.empty())
	{
		CurTile.Data = DefaultSprite->GetSpriteData(_Parameter.Index);
	}
	else
	{
		auto FindSprite = GameEngineSprite::Find(_Parameter.SpriteName);
		CurTile.Data = FindSprite->GetSpriteData(_Parameter.Index);
	}

	CurTile.Index = _Parameter.Index;
}

void GameEngineTilemap::Render(GameEngineCamera* _Camera, float _Delta)
{
	ResSetting();

	float4 CameraPos = _Camera->Transform.GetWorldPosition();
	float4 WindowScale = GameEngineWindow::GetInst().GetScale();

	float4 ScreenLeftTop;

	ScreenLeftTop.X = CameraPos.X - WindowScale.hX();
	ScreenLeftTop.Y = CameraPos.Y - WindowScale.hY();

	int StartX = static_cast<int>(ScreenLeftTop.X / TileData.TileScale.X) - 1;
	int StartY = static_cast<int>(ScreenLeftTop.Y / TileData.TileScale.Y) - 1;
	int EndX = StartX + static_cast<int>(WindowScale.X / TileData.TileScale.X) + 1;
	int EndY = StartY + static_cast<int>(WindowScale.Y / TileData.TileScale.Y) + 1;

	if (0 >= StartX)
	{
		StartX = 0;
	}

	if (0 >= EndX)
	{
		EndX = 0;
	}

	if (TileData.TileCountX < StartX)
	{
		StartX = static_cast<int>(TileData.TileCountX) - 1;
	}

	if (TileData.TileCountX < EndX)
	{
		EndX = static_cast<int>(TileData.TileCountX) - 1;
	}

	if (0 >= StartY)
	{
		StartY = 0;
	}

	if (0 >= EndY)
	{
		EndY = 0;
	}

	if (TileData.TileCountX < StartY)
	{
		StartX = static_cast<int>(TileData.TileCountX) - 1;
	}

	if (TileData.TileCountY < EndY)
	{
		EndX = static_cast<int>(TileData.TileCountX) - 1;
	}

	TransformData Data{};
	for (int y = StartY; y < EndY; ++y)
	{
		for (int x = StartX; x < EndX; ++x)
		{
			if (Tiles[y][x].Index < 0)
			{
				continue;
			}

			auto CB1 = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData");

			if (CB1)
			{
				float4 Pos{};
				Pos = Transform.GetWorldPosition();
				Pos.X += TileData.TileScale.X * static_cast<float>(x) + TileData.TileScale.hX();
				Pos.Y -= TileData.TileScale.Y * static_cast<float>(y) + TileData.TileScale.hY();

				Data = Transform.GetConstTransformDataRef();
				Data.Position = Pos;
				Data.Scale = TileData.TileScale;
				Data.LocalCalculation();

				Data.ParentMatrix = Transform.GetConstTransformDataRef().WorldMatrix;
				Data.WorldMatrix = Data.LocalWorldMatrix * Data.ParentMatrix;
				Data.WorldViewProjectionCalculation();

				CB1->ChangeData(Data);
				CB1->Setting(0);
			}

			SpriteData& TileSprite = Tiles[y][x].Data;

			auto CB2 = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData");
			if (CB2)
			{
				CB2->ChangeData(TileSprite.Pivot);
				CB2->Setting(1);
			}

			Tiles[y][x].Data.Texture->PSSetting(0);

			Draw();
		}
	}
}
