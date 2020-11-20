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

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};