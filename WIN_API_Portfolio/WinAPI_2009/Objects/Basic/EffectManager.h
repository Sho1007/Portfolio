#pragma once

class EffectManager
{
private:
	typedef vector<Effect*> Effects;
	map<string, Effects> totalEffect;

	EffectManager();
	~EffectManager();
public :
	static EffectManager* Get()
	{
		static EffectManager instance;
		return &instance;
	}

	void Update();
	void Render();

	void Add(string key, Texture* texture, UINT poolCount, float speed = 0.1f);

	void Play(string key, Vector2 pos);
};