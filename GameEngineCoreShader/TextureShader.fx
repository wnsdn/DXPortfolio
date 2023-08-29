#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct PixelOutput
{
    float4 POSITION : SV_Position;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutput TextureShader_VS(GameEngineVertex2D _Input)
{
    PixelOutput Result = (PixelOutput) 0;

    Result.POSITION = mul(_Input.POSITION, WorldViewPorjectionMatrix);
    Result.TEXCOORD = _Input.TEXCOORD;
    
    return Result;
}

Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 TextureShader_PS(PixelOutput _Input) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(Sampler, _Input.TEXCOORD.xy);

    if (0.0f >= Color.a)
    {
        clip(-1);
    }

    return Color;
}