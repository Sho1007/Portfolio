#pragma once

class Bar : public Rect
{
private:
	float speed;

	HBRUSH brush;
public:
	Bar();
	~Bar();

	void Update();
	void Render(HDC hdc);
};