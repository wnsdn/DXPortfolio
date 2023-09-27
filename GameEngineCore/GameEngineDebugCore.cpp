#include "PreCompile.h"
#include "GameEngineDebugCore.h"
#include "GameEngineRenderUnit.h"
#include "GameEngineLevel.h"

class GameEngineDebugInfo
{
public:
	float4 Color = float4::RED;
	TransformData Data;
	GameEngineCamera* Camera;
	GameEngineRenderUnit Unit;
};

std::vector<GameEngineDebugInfo> DebugUnit;
GameEngineLevel* GameEngineDebug::GameEngineDebugCore::CurLevel = nullptr;

void GameEngineDebug::GameEngineDebugCore::DebugInit()
{
	DebugUnit.resize(100);
}

void GameEngineDebug::GameEngineDebugCore::DebugRender()
{
	for (auto& Unit : DebugUnit)
	{
		Unit.Unit.ResSetting();
		Unit.Unit.Draw();
	}

	DebugUnit.clear();
}

void GameEngineDebug::DrawBox2D(const GameEngineTransform& _Trans, float4 _Color, GameEngineCamera* _Camera)
{
	GameEngineDebug::DrawBox2D(_Trans.GetWorldScale(), _Trans.GetWorldRotationEuler(), _Trans.GetWorldPosition(), _Color, _Camera);
}

void GameEngineDebug::DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color, GameEngineCamera* _Camera)
{
	if (!_Camera)
	{
		_Camera = GameEngineDebug::GameEngineDebugCore::CurLevel->GetMainCamera().get();
	}

	GameEngineDebugInfo& Value = DebugUnit.emplace_back();
	Value.Camera = _Camera;
	Value.Unit.SetMesh("Rect");
	Value.Unit.SetMaterial("2DTextureWire");

	Value.Color = _Color;
	Value.Data.Scale = _Scale;
	Value.Data.Rotation = _Rot;
	Value.Data.Position = _Pos;
	Value.Data.LocalCalculation();
	Value.Data.ViewMatrix = _Camera->Transform.GetConstTransformDataRef().ViewMatrix;
	Value.Data.ProjectionMatrix = _Camera->Transform.GetConstTransformDataRef().ProjectionMatrix;
	Value.Data.WorldViewProjectionCalculation();

	Value.Unit.ShaderResHelper.SetConstantBufferLink("TransformData", Value.Data);
	Value.Unit.ShaderResHelper.SetConstantBufferLink("DebugColor", Value.Color);
}
