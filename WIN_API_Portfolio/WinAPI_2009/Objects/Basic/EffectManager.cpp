#include "Framework.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
		{
			delete effect;
		}
	}
}

void EffectManager::Update()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
		{
			effect->Update();
		}
	}
}

void EffectManager::Render()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
		{
			effect->Render();
		}
	}
}

void EffectManager::Add(string key, Texture* texture, UINT poolCount, float speed)
{
	Effects effects;

	for (int i = 0; i < poolCount; ++i)
	{
		effects.emplace_back(new Effect(texture, speed));
	}

	totalEffect[key] = effects;
}

void EffectManager::Play(string key, Vector2 pos)
{
	if (totalEffect.count(key) == 0)
		return;

	for (Effect* effect : totalEffect[key])
	{
		if (!effect->isActive)
		{
			effect->Play(pos);
			return;
		}
	}
}
