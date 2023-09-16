#pragma once

#include <Windows.h>
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

#define SafeRelease(_obj)\
if (_obj)\
{\
	_obj->Release();\
	_obj = nullptr;\
}\

#define SafeDelete(_obj)\
if (_obj)\
{\
	delete _obj;\
	_obj = nullptr;\
}\

#define	Check(_bool) assert(SUCCEEDED(_bool));
