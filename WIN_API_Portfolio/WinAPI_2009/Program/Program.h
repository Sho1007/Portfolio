#pragma once

class Program
{
private:
	static HDC backBuffer;
	HBITMAP hBitmap;
public:
	Program();
	~Program();

	void Update();
	void Render(HDC hdc);

	void CreateBackBuffer();

	static HDC BackBuffer() { return backBuffer; }
};