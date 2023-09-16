#include "PreCompile.h"
#include "GameEngineSound.h"

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
	FMOD_Check(FMOD::System_Create(&System));
	FMOD_Check(System->init(32, FMOD_INIT_NORMAL, nullptr));
}

void GameEngineSound::Update()
{
	FMOD_Check(System->update());

	for (auto& Pair : AllSound)
	{
		auto GESound = Pair.second;
		auto Channel = GESound->Channel;

		bool IsPlaying = false;
		Channel->isPlaying(&IsPlaying);
		if (!IsPlaying)
		{
			continue;
		}

		UINT Position = 0;
		Channel->getPosition(&Position, FMOD_TIMEUNIT_MS);

		if (!GESound->Once && Position <= 1000)
		{
			++GESound->NumberOfRepetitions;
			GESound->Once = true;
		}
		else if (Position > 1000)
		{
			GESound->Once = false;
		}
	}
}

void GameEngineSound::SoundRelease()
{
	for (auto& Pair : AllSound)
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

void GameEngineSound::CreateSound(std::string_view _Path, bool _Loop)
{
	GameEnginePath Path;
	Path.SetPath(_Path);

	std::string Filename = Path.GetFilename();

	auto FindIter = AllSound.find(Filename);
	if (FindIter != AllSound.end())
	{
		return;
	}

	GameEngineSound* NewSound = new GameEngineSound();

	FMOD_MODE Mode = FMOD_DEFAULT;
	if (_Loop)
	{
		Mode = FMOD_LOOP_NORMAL;
	}

	FMOD_Check(System->createSound(Path.GetPath().c_str(), Mode, nullptr, &NewSound->Sound));

	AllSound.emplace(Filename, NewSound);
}

GameEngineSound* GameEngineSound::FindSound(const std::string& _Name)
{
	auto FindIter = AllSound.find(_Name);
	if (FindIter == AllSound.end())
	{
		assert(false);
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSound::Play()
{
	System->playSound(Sound, nullptr, false, &Channel);
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

