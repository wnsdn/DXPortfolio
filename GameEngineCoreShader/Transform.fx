
cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;
    
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;
    
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;
    
    float4x4 ScaleMatrix;           // 크기
    float4x4 RotationMatrix;        // 자전
    float4x4 PositionMatrix;        // 이동
    float4x4 RevolutionMatrix;      // 공전
    float4x4 ParentMatrix;          // 부모
    
    float4x4 LocalWorldMatrix;
    
    float4x4 WorldMatrix;
    
    float4x4 ViewMatrix;
    float4x4 ProjectionMatrix;
    float4x4 ViewPort;
    
    float4x4 WorldViewProjectionMatrix;
};

cbuffer SpriteData : register(b1)
{
    float Pos2DX;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
};

cbuffer AlphaData : register(b2)
{
    float4 Alpha;
};

cbuffer SpriteRendererInfo : register(b3)
{
    int FlipLeft = 0;
    int FlipUp = 0;
    float Temp1;
    float Temp2;
}
