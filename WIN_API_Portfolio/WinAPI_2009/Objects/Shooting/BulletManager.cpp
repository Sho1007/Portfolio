#include "Framework.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	for(auto bullets : totalBullet)
	{
		for (Bullet* bullet : bullets.second)
		{
			delete bullet;
		}
		bullets.second.clear();
	}
	totalBullet.clear();
}

void BulletManager::Update()
{
	for (auto bullets : totalBullet)
	{
		for (Bullet* bullet : bullets.second)
		{
			bullet->Update();
		}
	}
}

void BulletManager::Render()
{
	for (auto bullets : totalBullet)
	{
		for (Bullet* bullet : bullets.second)
		{
			bullet->Render();
		}
	}
}

void BulletManager::CreateBullet(string key, Texture* texture, UINT poolCount)
{
	if (totalBullet.count(key) > 0)
		return;

	vector<Bullet*> bullets(poolCount);	// 미리 리사이징 해줘야 나중에 사이즈넘쳤을때 지우고 복붙하는 과정을 줄일 수 있음

	for (UINT i = 0; i < poolCount; ++i)
	{
		bullets[i] = new Bullet(texture);
	}

	totalBullet[key] = bullets;
}

void BulletManager::Fire(string key, Vector2 pos, float angle, float speed, float damage)
{
	if (totalBullet.count(key) == 0)
		return;

	for (Bullet* bullet : totalBullet[key])
	{
		if (!bullet->isActive)
		{
			bullet->Fire(pos, angle, speed, damage);
			return;
		}
	}
}

void BulletManager::Fire(string key, Vector2 pos, float angle, float speed, float damage, POINT frame)
{
	if (totalBullet.count(key) == 0)
		return;

	for (Bullet* bullet : totalBullet[key])
	{
		if (!bullet->isActive)
		{
			bullet->SetFrame(frame);
			bullet->Fire(pos, angle, speed, damage);
			return;
		}
	}
}

bool BulletManager::IsCollision(string key, Rect* rect)
{
	if (totalBullet.count(key) == 0)
		return false;

	for (Bullet* bullet : totalBullet[key])
	{
		if (bullet->IsRectCollision(rect))
		{
			rect->Damage(bullet->GetDamage());
			EFFECT->Play("exp", rect->center);
			AUDIO->Play("exp");
			bullet->isActive = false;
			return true;
		}
	}

	return false;
}
