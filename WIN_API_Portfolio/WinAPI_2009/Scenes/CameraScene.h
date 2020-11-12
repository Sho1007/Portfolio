#pragma once

class CameraScene : public Scene
{
private:
	ImageRect* mapSky;
	ImageRect* mapBG;
	ImageRect* mapLand;

	Angie* angie;
public:
	CameraScene();
	~CameraScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};