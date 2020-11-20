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

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};