#pragma once

class GameEngineInputLayoutInfo
{
public:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Infos;
	int Offset = 0;

	static UINT FormatSize(DXGI_FORMAT _Format);
	void AddInputLayoutDesc(
		LPCSTR _SemanticName,
		DXGI_FORMAT _Format,
		UINT _SemanticIndex = 0,
		UINT _AlignedByteOffset = -1,
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
		UINT _InputSlot = 0,
		UINT _InstanceDataStepRate = 0);
};

class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineInputLayout
{
private:
	ID3D11InputLayout* Layout = nullptr;
public:
	void ResCreate(
		std::shared_ptr<GameEngineVertexBuffer> _Buffer,
		std::shared_ptr<GameEngineVertexShader> _Shader);
	void Setting();

	GameEngineInputLayout() {}
	~GameEngineInputLayout();
	GameEngineInputLayout(const GameEngineInputLayout&) = delete;
	GameEngineInputLayout(GameEngineInputLayout&&) noexcept = delete;
	void operator=(const GameEngineInputLayout&) = delete;
	void operator=(GameEngineInputLayout&&) noexcept = delete;
};