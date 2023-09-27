#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 Position : POSITION;
};

struct PixelOutput
{
    float4 Position : SV_Position;
};

PixelOutput DebugColor_VS(GameEngineVertex2D _Input)
{
    PixelOutput Result = (PixelOutput) 0;
    
    Result.Position = mul(_Input.Position, WorldViewProjectionMatrix);

    return Result;
}

cbuffer DebugColor : register(b0)
{
    float4 Color;
}

float4 DebugColor_PS(PixelOutput _Input) : SV_Target
{
    return Color;
}
