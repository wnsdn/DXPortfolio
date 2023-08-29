#include "PreCompile.h"
#include "GameEngineSprite.h"

float4 SpriteData::GetScale()
{
    return Texture->GetScale();
}

void GameEngineSprite::ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
{
    auto Texture = GameEngineTexture::Find(_Name);

    SpriteDatas.resize(_X * _Y);

    for (size_t y = 0; y < _Y; y++)
    {
        for (size_t x = 0; x < _X; x++)
        {
            auto Index = (y * _X) + x;
            SpriteDatas[Index].Texture = Texture;
        }
    }
}

const SpriteData& GameEngineSprite::GetSpriteData(unsigned int _Index)
{
    if (_Index >= SpriteDatas.size())
    {
        MsgBoxAssert("인덱스를 오버해서 스프라이트 데이터를 가져오려고 했습니다.");
        return SpriteData();
    }

    return SpriteDatas[_Index];
}
