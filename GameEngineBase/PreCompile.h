#pragma once

#include <Windows.h>
#include <assert.h>

#include <map>
#include <list>
#include <set>
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <memory>
#include <chrono>
#include <functional>
#include <algorithm>
#include <filesystem>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "GameEngineDebug.h"

using namespace std::literals;

#define SafeRelease(Input)\
if (Input)\
{\
	Input->Release();\
	Input = nullptr;\
}\

#define SafeDelete(Input)\
if (Input)\
{\
	delete Input;\
	Input = nullptr;\
}\

#define	Check(Input) assert(SUCCEEDED(Input));
