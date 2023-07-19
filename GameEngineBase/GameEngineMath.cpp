#include "PreCompile.h"
#include "GameEngineMath.h"

const float4 float4::Left = { -1.0f, 0.0f };
const float4 float4::Right = { 1.0f, 0.0f };
const float4 float4::Up = { 0.0f, -1.0f };
const float4 float4::Down = { 0.0f, 1.0f };

const float GameEngineMath::PI = 3.1415926f;
const float GameEngineMath::PI2 = PI * 2.0f;
const float GameEngineMath::D2R = GameEngineMath::PI / 180.0f;
const float GameEngineMath::R2D = 180.0f / GameEngineMath::PI;