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

    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    
    Result.TEXCOORD.x = (_Input.TEXCOORD.x * Scale2DX) + Pos2DX;
    Result.TEXCOORD.y = (_Input.TEXCOORD.y * Scale2DY) + Pos2DY;
    
    return Result;
}

Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 TextureShader_PS(PixelOutput _Input) : SV_Target
{
    float4 Color = DiffuseTex.Sample(Sampler, _Input.TEXCOORD.xy);

    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    Color.a = Alpha.a;

    return Color;
}