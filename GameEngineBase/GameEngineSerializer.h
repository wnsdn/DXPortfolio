#pragma once
#include <vector>

class GameEngineSerializer
{
private:
	std::vector<char> Data;
public:
	void SetSize(size_t _Size)
	{
		Data.resize(_Size);
	}
	size_t GetSize() const
	{
		return Data.size();
	}

	template <typename PtrType>
	PtrType* GetDataPtr()
	{
		return reinterpret_cast<PtrType*>(&Data[0]);
	}
};

