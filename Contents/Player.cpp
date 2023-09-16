#include "PreCompile.h"
#include "Player.h"

#include "Tile_Main.h"

void Player::Init(std::shared_ptr<Tile_Main> _CurTile)
{
	CurTile = _CurTile;
	Transform.SetLocalPosition(CurTile->Transform.GetLocalPosition());
}

void Player::SoundUpdate(UINT _Repeat)
{
	static UINT Repeat = _Repeat;

	if (Repeat != _Repeat)
	{
		Repeat = _Repeat;
		Transform.SetLocalRotation({ 0.0f, 0.0f, 230.0f });
	}
}

void Player::Start()
{
	Orbit = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	Orbit->SetSprite("redorbit.png");
	Orbit->SetImageScale({ 1.0f, 1.0f });
	Orbit->SetAlpha(0.7f);

	for (int i = 0; i < EffectNum; ++i)
	{
		Effect[i] = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
		Effect[i]->SetSprite("blueeffect.png");
		Effect[i]->SetImageScale({ 38.0f, 38.0f });
		Effect[i]->Transform.SetParentCalc(false);
		Effect[i]->SetAlpha(0.5f);
	}

	Ball1 = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	Ball1->SetSprite("redball.png");
	Ball1->SetImageScale({ 38.0f, 38.0f });

	Ball2 = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	Ball2->SetSprite("blueball.png");
	Ball2->SetImageScale({ 38.0f, 38.0f });
	Ball2->Transform.AddLocalPosition({ -55.0f });

	Transform.SetLocalRotation({ 0.0f, 0.0f, 230.0f });

	Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
	Col->Transform.SetLocalScale({ 38.0f, 38.0f });
	Col->Transform.AddLocalPosition(Ball2->Transform.GetLocalPosition());
}

void Player::Update(float _Delta)
{
	if (Orbit->GetImageScale().X <= 110.0f)
	{
		float OrbitScaleSpeed = 500.0f;
		Orbit->AddImageScale({ OrbitScaleSpeed * _Delta, OrbitScaleSpeed * _Delta });
	}

	auto CamPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();
	auto MyPos = Transform.GetLocalPosition();
	MyPos.Y = -55.0f;

	static float4 Diff{};
	if (IsMove)
	{
		Diff = MyPos - CamPos;
		IsMove = false;
	}

	if (float4::Length2D(CamPos, MyPos) >= 2.0f && IsOnWorldTile)
	{
		CamPos.X += Diff.X * _Delta;
		CamPos.Y += Diff.Y * _Delta;
		GetLevel()->GetMainCamera()->Transform.SetLocalPosition(CamPos);
	}

	auto& Others = CurTile->Others;
	std::shared_ptr<Tile_Main> NextTile = nullptr;
	Col->Collision(ContentsCollisionType::Tile, [&Others, &NextTile](std::vector<std::shared_ptr<GameEngineCollision>>& _Cols)
		{
			for (auto& _Col : _Cols)
			{
				for (auto& Other : Others)
				{
					if (Other->Col == _Col)
					{
						NextTile = Other;
					}
				}
			}
		});

	float RotSpeed = 360.0f;//¼öÁ¤
	Transform.AddLocalRotation({ 0.0f, 0.0f, -RotSpeed * _Delta });
	Orbit->Transform.AddLocalRotation({ 0.0f, 0.0f, (RotSpeed - 35.0f) * _Delta });

	for (int i = 0; i < EffectNum; ++i)
	{
		if (!Deploy[i])
		{
			if (Ball1->IsCurSprite("redball.png"))
			{
				Effect[i]->SetSprite("blueeffect.png");
			}
			else
			{
				Effect[i]->SetSprite("redeffect.png");
			}
			Effect[i]->SetImageScale({ 38.0f, 38.0f, 1.0f });
			Effect[i]->Transform.SetLocalPosition(Ball2->Transform.GetWorldPosition());
			Deploy[i] = true;
			break;
		}
		else if (Deploy[i])
		{
			float ScaleSpeed = 250.0f * _Delta;
			Effect[i]->AddImageScale({ -ScaleSpeed, -ScaleSpeed, 0.0f });
			if (Effect[i]->GetImageScale().Y <= 5.0f)
			{
				Deploy[i] = false;
			}
		}
	}

	if (GameEngineInput::IsDown('Q') && NextTile)
	{
		Transform.SetLocalPosition(NextTile->Transform.GetWorldPosition());
		Transform.AddLocalRotation({ 0.0f, 0.0f, 180.0f });

		if (Ball1->IsCurSprite("redball.png"))
		{
			Ball1->SetSprite("blueball.png");
			Ball2->SetSprite("redball.png");
			Orbit->SetSprite("blueorbit.png");
		}
		else
		{
			Ball1->SetSprite("redball.png");
			Ball2->SetSprite("blueball.png");
			Orbit->SetSprite("redorbit.png");
		}

		Ball1->SetImageScale({ 38.0f, 38.0f });
		Ball2->SetImageScale({ 38.0f, 38.0f });
		Orbit->SetImageScale({ 1.0f, 1.0f });
		Col->Transform.SetLocalPosition(Ball2->Transform.GetLocalPosition());

		CurTile = NextTile;

		if (IsOnWorldTile)
		{
			IsMove = true;
		}
	}
}
