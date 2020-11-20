#pragma once

class StartScene : public Scene
{
	Button* startBtn;
	Button* mapToolBtn;
	Button* exitBtn;
	Texture* bg;

	void Create();
	void Destroy();

	void StartAction();
	void ToolAction();

	void Exit();
public:
	StartScene();
	~StartScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};