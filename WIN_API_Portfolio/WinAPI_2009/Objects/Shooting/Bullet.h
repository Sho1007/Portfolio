#pragma once

class Bullet : public ImageRect
{
private:
	float speed;
	float angle;
	float damage;
public:
	Bullet(Texture* texture);
	~Bullet();

	void Update();
	void Render();

	void Fire(const Vector2 pos, const float angle, const float speed, float damage);
	float GetDamage() { return damage; }
	void SetFrame(POINT value) { frame = value; }
};