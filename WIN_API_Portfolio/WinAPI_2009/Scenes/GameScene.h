#pragma once

class GameScene : public Scene
{
	Texture* bg;
	Map* map;
	Player* player;

	void Create();
	void Destroy();
public :
	GameScene();
	~GameScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};