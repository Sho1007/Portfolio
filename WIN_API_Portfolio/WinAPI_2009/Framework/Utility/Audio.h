#pragma once

#define MAX_CHANNEL 15

using namespace FMOD;

struct SoundInfo
{
	Sound* sound;
	Channel* channel;

	SoundInfo()
		: sound(nullptr), channel(nullptr)
	{}

	~SoundInfo()
	{
		sound->release();
	}
};

class Audio
{
	
private:
	System* soundSystem;

	map<string, SoundInfo*> sounds;

	Audio();
	~Audio();
public:
	static Audio* Get()
	{
		static Audio instance;
		return &instance;
	}

	void Update();

	void Add(string key, string file, bool bgm = false);

	void Play(string key, float value = 1.0f);

	void Stop(string key);

	void Pause(string key);

	void Resume(string key);

	bool isPlaySound(string key);
};