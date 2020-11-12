#pragma once

class BulletManager
{
private:
	map<string, vector<Bullet*>> totalBullet;

public:
	BulletManager();
	~BulletManager();

	void Update();
	void Render();

	void CreateBullet(string key, Texture* texture, UINT poolCount);

	void Fire(string key, Vector2 pos, float angle, float speed, float damage);

	void Fire(string key, Vector2 pos, float angle, float speed, float damage, POINT frame);

	bool IsCollision(string key, Rect* rect);
};