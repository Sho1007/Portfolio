#pragma once

class HWShootingScene : public Scene
{
	BulletManager* bm;
	HWDragonEnemyManager* em;

	DragonLandscape* landscape;
	HWDragonPlayer* player;
public :
	HWShootingScene();
	~HWShootingScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void End() override;

	void CreateEffect();
};