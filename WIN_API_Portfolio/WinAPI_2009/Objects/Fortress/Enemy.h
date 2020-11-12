#pragma once

class Enemy : public ImageRect
{
private:
	static const float MAX_HP;
	float speed;

	Vector2 direction;

	HpBar* hpBar;
	Animation* animation;
public:
	Enemy(Texture* texture);
	~Enemy();

	void Update();
	void Render();

	void Spawn(Vector2 pos);

	void Damage(float damage);
};