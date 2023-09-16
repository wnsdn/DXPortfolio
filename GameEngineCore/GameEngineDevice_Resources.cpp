#include "PreCompile.h"
#include "GameEngineDevice.h"

#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineInputLayout.h"

#include "GameEngineTransform.h"
#include "GameEngineConstantBuffer.h"

#include "GameEngineRasterizer.h"
#include "GameEngineSampler.h"
#include "GameEngineBlend.h"

#include "GameEngineTexture.h"
#include "GameEngineSprite.h"

void GameEngineDevice::ResourcesInit()
{
	//Shader Load
	{
		GameEngineDirectory Dir;
		Dir.SetFilenameToPath("GameEngineCoreShader");
		auto AllPath = Dir.GetAllPathByExt({ ".fx" });
		for (auto& Path : AllPath)
		{
			GameEngineFile File;
			File.SetPath(Path.GetPath());
			GameEngineShader::AutoCompile(File);
		}
	}

	//GER Texture Load
	/*{
		GameEngineDirectory Dir;
		Dir.SetFilenameToPath("GameEngineResources");
		auto AllPath = Dir.GetAllFileInDir("Texture");
		for (auto& Path : AllPath)
		{
			GameEngineTexture::Load(Path.GetPath());
		}
	}

	GameEngineSprite::CreateSingle("NSet.png");*/

	//VB
	std::vector<GameEngineVertex2D>Vertex
	{
		{{-0.5f, 0.5f, 0.0f, 1.0f},{0.0f, 0.0f}},
		{{0.5f, 0.5f, 0.0f, 1.0f},{1.0f, 0.0f}},
		{{0.5f, -0.5f, 0.0f, 1.0f},{1.0f, 1.0f}},
		{{-0.5f, -0.5f, 0.0f, 1.0f},{0.0f, 1.0f}}
	};
	GameEngineVertexBuffer::Create("Rect", Vertex);

	//IB
	std::vector<unsigned int> Index{ 0, 1, 2, 2, 3, 0 };
	GameEngineIndexBuffer::Create("Rect", Index);

	//CB Transform
	GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex, 0);

	// Rasterizer
	{
		D3D11_RASTERIZER_DESC Desc{};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GameEngineRasterizer::Create("Rasterizer", Desc);
	}

	//Blend
	{
		D3D11_BLEND_DESC Desc{};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GameEngineBlend::Create("Blend", Desc);
	}

	// Sampler
	{
		D3D11_SAMPLER_DESC Desc{};
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = FLT_MIN;
		Desc.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("LINEAR", Desc);
	}
	// Sampler
	{
		D3D11_SAMPLER_DESC Desc{};
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = FLT_MIN;
		Desc.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("POINT", Desc);
	}
}
