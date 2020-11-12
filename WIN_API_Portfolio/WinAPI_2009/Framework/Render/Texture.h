#pragma once

class Rect;

class Texture
{
private:
	friend class TextureManager;

	HDC memDC;
	HDC alphaMemDC;
	HBITMAP bitmap;
	HBITMAP alphaBitmap;

	COLORREF transColor;

	POINT originSize;
	POINT frameSize;
	POINT maxFrame;

	wstring file;

	BLENDFUNCTION blendFunc;

	Texture(wstring file, int width, int height, COLORREF transColor = MAGENTA);
	Texture(wstring file, int width, int height,
		int frameX, int frameY, COLORREF transColor = MAGENTA);
	~Texture();
public:
	void Create();

	void Render(Rect* rect);
	void Render(Rect* rect, POINT curFrame);
	void Render(Rect* rect, RECT rectFrame);
	void Render(Rect* rect, int alpha);
	void Render(Rect* rect, POINT curFrame, int alpha);

	Vector2 GetSize() { return Vector2(frameSize.x, frameSize.y); } 
	POINT GetMaxFrame() { return maxFrame; }

	HDC GetMemDC() { return memDC; }
};