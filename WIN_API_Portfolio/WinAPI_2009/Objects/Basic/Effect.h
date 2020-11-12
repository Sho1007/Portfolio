#pragma once

class Effect : public ImageRect
{
private:
	Animation* animation;
public:
	Effect(Texture* texture, float speed = 0.1f);
	~Effect();

	void Update();
	void Render();

	void Play(Vector2 pos);
	void End();
};