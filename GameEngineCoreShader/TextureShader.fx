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
    
    float4 CalUV = _Input.TEXCOORD;
    
    if (FlipLeft)
    {
        CalUV.x *= -1;
        CalUV.x += 1;
    }
    
    if (FlipUp)
    {
        CalUV.y *= -1;
        CalUV.y += 1;
    }
    
    Result.TEXCOORD.x = (CalUV.x * Scale2DX) + Pos2DX;
    Result.TEXCOORD.y = (CalUV.y * Scale2DY) + Pos2DY;
    
    Result.TEXCOORD.w = Alpha.a;
    
    return Result;
}

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

float4 TextureShader_PS(PixelOutput _Input) : SV_Target
{
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);

    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    Color.a = _Input.TEXCOORD.w;

    return Color;
}