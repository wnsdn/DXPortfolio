#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

FMOD::System* GameEngineSound::System = nullptr;
std::map<std::string, GameEngineSound*> GameEngineSound::AllSound;

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
	if (Sound)
	{
		Sound->release();
		Sound = nullptr;
	}
}

void GameEngineSound::Init()
{
	if (FMOD::System_Create(&System) != FMOD_OK)
	{
		MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
		return;
	}

	if (System->init(32, FMOD_INIT_NORMAL, nullptr) != FMOD_OK)
	{
		MsgBoxAssert("사운드 시스템 이니셜라이즈에 실패했습니다.");
		return;
	}
}

void GameEngineSound::Update()
{
	if (System->update() != FMOD_OK)
	{
		MsgBoxAssert("System->update()");
		return;
	}
}

void GameEngineSound::SoundRelease()
{
	for (auto& Pair : GameEngineSound::AllSound)
	{
		GameEngineSound* Sound = Pair.second;

		if (Sound)
		{
			delete Sound;
			Sound = nullptr;
		}
	}
}

void GameEngineSound::SystemRelease()
{
	if (System)
	{
		System->release();
		System = nullptr;
	}
}

void GameEngineSound::CreateSound(const std::string& _Filename, bool _Loop)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Filename);
	auto FindIter = AllSound.find(Upper);

	if (FindIter != AllSound.end())
	{
		return;
	}

	GameEngineSound* NewSound = new GameEngineSound();

	FMOD_RESULT Result{};
	if (_Loop)
	{
		Result = System->createSound(GameEnginePath::FilenameToPath(_Filename).c_str(), FMOD_LOOP_NORMAL, nullptr, &NewSound->Sound);
	}
	else
	{
		Result = System->createSound(GameEnginePath::FilenameToPath(_Filename).c_str(), FMOD_DEFAULT, nullptr, &NewSound->Sound);
	}

	if (Result != FMOD_OK)
	{
		MsgBoxAssert(_Filename + "System->createSound()");
		return;
	}

	AllSound.emplace(Upper, NewSound);
}

GameEngineSound* GameEngineSound::FindSound(const std::string& _Filename)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Filename);
	auto FindIter = AllSound.find(Upper);

	if (FindIter == AllSound.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSound::Play()
{
	System->playSound(Sound, nullptr, false, &Channel);
	Channel->setVolume(0.3f);
}

void GameEngineSound::Stop()
{
	Channel->stop();
}

void GameEngineSound::SetVolume(float _Volume)
{
	if (_Volume >= 1.0f)
	{
		_Volume = 1.0f;
	}
	else if (_Volume <= 0.0f)
	{
		_Volume = 0.0f;
	}
	Channel->setVolume(_Volume);
}

