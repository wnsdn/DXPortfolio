#pragma once

#include <Windows.h>
#include <map>
#include <list>
#include <set>
#include <vector>

#include <string>
#include <string_view>
#include <memory>
#include <chrono>
#include <functional>
#include <algorithm>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "GameEngineDebug.h"

#define SafeRelease(OBJ)\
if (OBJ)\
{\
	OBJ->Release();\
	OBJ = nullptr;\
}\

#define SafeDelete(OBJ)\
if (OBJ)\
{\
	delete OBJ;\
	OBJ = nullptr;\
}\
