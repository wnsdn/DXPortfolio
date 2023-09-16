#include "PreCompile.h"
#include "TitleLevel.h"

#include "Background.h"
#include "Tile_Main.h"
#include "Tile_Play.h"
#include "Player.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	float4 HalfWndScale = GameEngineWindow::GetInst().GetScale().Half();

	{
		GameEngineDirectory Dir;
		Dir.SetFilenameToPath("ContentsResources");
		auto AllPath = Dir.GetAllFileInDir("Texture");
		for (auto& Path : AllPath)
		{
			GameEngineFile File;
			File.SetPath(Path.GetPath());
			GameEngineTexture::Load(File.GetPath());
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.SetFilenameToPath("ContentsResources");
		auto AllPath = Dir.GetAllFileInDir("Sound");
		for (auto& Path : AllPath)
		{
			GameEngineSound::CreateSound(Path.GetPath(), true);
		}
	}

	GameEngineSprite::CreateSingle("title_bg.png");

	GameEngineSprite::CreateSingle("tile_unlit.png");
	GameEngineSprite::CreateSingle("bottomglow_E.png");
	GameEngineSprite::CreateSingle("bottomglow_F.png");
	GameEngineSprite::CreateCut("tiles.png", 1, 13);

	GameEngineSprite::CreateSingle("blueball.png");
	GameEngineSprite::CreateSingle("redball.png");
	GameEngineSprite::CreateSingle("blueeffect.png");
	GameEngineSprite::CreateSingle("redeffect.png");
	GameEngineSprite::CreateSingle("blueorbit.png");
	GameEngineSprite::CreateSingle("redorbit.png");

	GameEngineSound::FindSound("main.mp3")->Play();

	float4 StartPos{};
	{
		CreateActor<Background>(ContentsObjectType::BackGround);

		float4 Pos{};
		for (int y = 0; y < MainY; ++y)
		{
			for (int x = 0; x < MainX; ++x)
			{
				MainTile[y][x] = CreateActor<Tile_Main>(ContentsObjectType::Tile);
				MainTile[y][x]->Init(Pos);
				if (y % 2 == 0 && x % 2 == 0 || y % 2 && x % 2)
				{
					MainTile[y][x]->SpriteChange();
				}

				Pos.X += 55.0f;
			}

			if (y != 4)
			{
				Pos.X = 0.0f;
				Pos.Y += 55.0f;
			}
		}

		for (int y = 0; y < MainY; ++y)
		{
			for (int x = 0; x < MainX; ++x)
			{
				if (x != 0)
				{
					MainTile[y][x]->Others.push_back(MainTile[y][x - 1]);
				}
				if (x != 4)
				{
					MainTile[y][x]->Others.push_back(MainTile[y][x + 1]);
				}
				if (y != 0)
				{
					MainTile[y][x]->Others.push_back(MainTile[y - 1][x]);
				}
				if (y != 4)
				{
					MainTile[y][x]->Others.push_back(MainTile[y + 1][x]);
				}

				if (x == 0 || x == 4 || y == 0 || y == 4)
				{
					MainTile[y][x]->Renderer->SetAlpha(0.0f);
					MainTile[y][x]->Effect->SetAlpha(0.0f);
				}
			}
		}

		for (int x = 0; x < WorldX; ++x)
		{
			WorldTile[x] = CreateActor<Tile_Main>(ContentsObjectType::Tile);
			WorldTile[x]->Init(Pos);
			if (x % 2)
			{
				WorldTile[x]->SpriteChange();
			}
			Pos.X += 55.0f;
		}

		MainTile[4][4]->Others.push_back(WorldTile[0]);
		WorldTile[0]->Others.push_back(MainTile[4][4]);

		for (int x = 0; x < WorldX; ++x)
		{
			if (x != 6)
			{
				WorldTile[x]->Others.push_back(WorldTile[x + 1]);
			}
			if (x != 0)
			{
				WorldTile[x]->Others.push_back(WorldTile[x - 1]);
			}

			WorldTile[x]->Renderer->SetAlpha(0.0f);
			WorldTile[x]->Effect->SetAlpha(0.0f);
		}

		StartPos = MainTile[2][2]->Transform.GetLocalPosition();
		StartPos.Z = -500.0f;

		MainPlayer = CreateActor<Player>(ContentsObjectType::Player);
		MainPlayer->Init(MainTile[2][2]);
	}

	{
		GetMainCamera()->Transform.SetLocalPosition(StartPos);
		GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	}
}

void TitleLevel::Update(float _Delta)
{
	static bool IsMove = false;
	static float4 Diff{};

	if (!MainPlayer->IsOnWorldTile)
	{
		if (MainPlayer->CurTile == WorldTile[0])
		{
			MainPlayer->IsOnWorldTile = true;
			MainPlayer->IsMove = true;
		}

		auto ToPos = MainTile[2][2]->Transform.GetLocalPosition();
		auto CamPos = GetMainCamera()->Transform.GetLocalPosition();

		if (IsMove)
		{
			Diff = ToPos - CamPos;
			IsMove = false;
		}

		if (float4::Length2D(ToPos, CamPos) >= 2.0f)
		{
			CamPos.X += Diff.X * _Delta;
			CamPos.Y += Diff.Y * _Delta;
			GetMainCamera()->Transform.SetLocalPosition(CamPos);
		}
	}
	else if (MainPlayer->IsOnWorldTile)
	{
		if (MainPlayer->CurTile == MainTile[4][4])
		{
			MainPlayer->IsOnWorldTile = false;
			MainPlayer->IsMove = false;

			IsMove = true;
		}
	}

	MainPlayer->SoundUpdate(GameEngineSound::FindSound("main.mp3")->GetNumberOfRepetitions());

	float AlphaSpeed = 9.0f;
	static bool TileOn = false;
	if (MainPlayer->CurTile == MainTile[2][2])
	{
		TileOn = true;

		for (int y = 0; y < MainY; ++y)
		{
			for (int x = 0; x < MainX; ++x)
			{
				if (x == 0 || x == 4 || y == 0 || y == 4)
				{
					MainTile[y][x]->Renderer->AddAlpha(-AlphaSpeed * _Delta);
					MainTile[y][x]->Effect->Off();
				}
			}
		}

		for (int x = 0; x < WorldX; ++x)
		{
			WorldTile[x]->Renderer->AddAlpha(-AlphaSpeed * _Delta);
			WorldTile[x]->Effect->Off();
		}
	}
	else
	{
		for (int y = 0; y < MainY; ++y)
		{
			for (int x = 0; x < MainX; ++x)
			{
				if (x == 0 || x == 4 || y == 0 || y == 4)
				{
					MainTile[y][x]->Renderer->AddAlpha(AlphaSpeed * _Delta);
					MainTile[y][x]->Effect->On();
				}
			}
		}

		for (int x = 0; x < WorldX; ++x)
		{
			WorldTile[x]->Renderer->AddAlpha(AlphaSpeed * _Delta);
			WorldTile[x]->Effect->On();
		}
		TileOn = false;
	}

	static float Time = 0.0f;
	Time += _Delta;
	float MinusTime = 0.5f;
	float TileAlpha = 0.3f;
	for (int y = 0; y < MainY; ++y)
	{
		for (int x = 0; x < MainX; ++x)
		{
			if (MainPlayer->CurTile == MainTile[y][x])
			{
				MainTile[y][x]->EffectOn = true;
			}

			if (MainTile[y][x]->EffectOn)
			{
				MainTile[y][x]->Effect->SetAlpha(TileAlpha);
			}

			if (Time >= MinusTime)
			{
				MainTile[y][x]->SpriteChange();
			}

			MainTile[y][x]->SpriteReset(GameEngineSound::FindSound("main.mp3")->GetNumberOfRepetitions());
		}
	}
	for (int x = 0; x < WorldX; ++x)
	{
		if (MainPlayer->CurTile == WorldTile[x])
		{
			WorldTile[x]->EffectOn = true;
		}

		if (WorldTile[x]->EffectOn)
		{
			WorldTile[x]->Effect->SetAlpha(TileAlpha);
		}

		if (Time >= MinusTime)
		{
			WorldTile[x]->SpriteChange();
		}

		WorldTile[x]->SpriteReset(GameEngineSound::FindSound("main.mp3")->GetNumberOfRepetitions());
	}

	if (Time >= MinusTime)
	{
		Time -= MinusTime;
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}
