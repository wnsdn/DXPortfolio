#include "PreCompile.h"
#include "GameEngineDevice.h"

#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEngineInputLayout.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineTransform.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEngineSampler.h"
#include "GameEngineTexture.h"
#include "GameEngineSprite.h"

void GameEngineDevice::ResourcesInit()
{
	std::vector<GameEngineVertex2D>Vertex
	{
		{{-0.5f, 0.5f, 0.0f, 1.0f},{0.0f, 0.0f}},
		{{0.5f, 0.5f, 0.0f, 1.0f},{1.0f, 0.0f}},
		{{0.5f, -0.5f, 0.0f, 1.0f},{1.0f, 1.0f}},
		{{-0.5f, -0.5f, 0.0f, 1.0f},{0.0f, 1.0f}}
	};
	GameEngineVertexBuffer::Create("Rect", Vertex);

	GameEngineDirectory Directory;
	Directory.SetPath("GameEngineCoreShader");
	std::vector<GameEngineFile> Files = Directory.GetAllFile({ ".fx" });
	for (auto& File : Files)
	{
		GameEngineShader::AutoCompile(File);
	}

	Directory.SetPath("GameEngineResources");
	std::vector<GameEngineFile> TFiles = Directory.GetAllTextureFile();
	for (auto& File : TFiles)
	{
		GameEngineTexture::Load(File.ToString(), File.GetFilename());
	}

	GameEngineSprite::CreateSingle("NSet.png");

	//IL

	std::vector<unsigned int> Index{ 0, 1, 2, 2, 3, 0 };
	GameEngineIndexBuffer::Create("Rect", Index);

	GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex, 0);

	//IA

	//VS
	//VS

	D3D11_RASTERIZER_DESC Desc{};
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	GameEngineRasterizer::Create("RasterizerState", Desc);

	//PS

	//OM

	D3D11_SAMPLER_DESC DescS{};
	DescS.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	DescS.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	DescS.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	DescS.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;

	DescS.MipLODBias = 0.0f;
	DescS.MaxAnisotropy = 1;
	DescS.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	DescS.MinLOD = -FLT_MAX;
	DescS.MaxLOD = FLT_MAX;

	auto Sampler = GameEngineSampler::Create("Sampler", DescS);
}
