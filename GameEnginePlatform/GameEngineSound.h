#pragma once
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

#define FMOD_Check(State) assert(State == FMOD_OK);

class GameEngineSound
{
public:
	static void Init();
	static void Update();
	static void SoundRelease();
	static void SystemRelease();

	static void CreateSound(std::string_view _Path, bool _Loop = false);
	static GameEngineSound* FindSound(const std::string& _Name);

	void Play();
	void Stop();
	void SetVolume(float _Volume);

	UINT GetNumberOfRepetitions() const
	{
		return NumberOfRepetitions;
	}
private:
	static FMOD::System* System;
	static std::map<std::string, GameEngineSound*> AllSound;

	FMOD::Sound* Sound = nullptr;
	FMOD::Channel* Channel = nullptr;
	UINT NumberOfRepetitions = 0;
	bool Once = false;

	GameEngineSound();
	~GameEngineSound();
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;
};

