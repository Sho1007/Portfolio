#include "Framework.h"

Texture::Texture(wstring file, int width, int height, COLORREF transColor)
	: file(file), originSize{width, height}, transColor(transColor)
{
	Create();

	frameSize = { width, height };
	maxFrame = { 1, 1 };
}

Texture::Texture(wstring file, int width, int height, int frameX, int frameY, COLORREF transColor)
	: file(file), originSize{ width, height }, transColor(transColor)
{
	Create();

	frameSize = { width / frameX, height / frameY };
	maxFrame = { frameX, frameY };
}

Texture::~Texture()
{
	DeleteDC(memDC);
	DeleteDC(alphaMemDC);
	DeleteObject(bitmap);
	DeleteObject(alphaBitmap);
}

void Texture::Create()
{
	HDC hdc = GetDC(hWnd);

	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);
	alphaBitmap = CreateCompatibleBitmap(hdc, originSize.x, originSize.y);

	ReleaseDC(hWnd, hdc);

	bitmap = (HBITMAP)LoadImage(hInst, file.c_str(),
		IMAGE_BITMAP, originSize.x, originSize.y, LR_LOADFROMFILE);

	SelectObject(memDC, bitmap);
	SelectObject(alphaMemDC, alphaBitmap);
}

void Texture::Render(Rect* rect)
{
	GdiTransparentBlt(
		Program::BackBuffer(),
		(int)(rect->Left()),
		(int)(rect->Top()),
		(int)(rect->size.x),
		(int)(rect->size.y),
		memDC,
		0, 0,
		frameSize.x, frameSize.y,
		transColor
	);
}

void Texture::Render(Rect* rect, POINT curFrame)
{
	GdiTransparentBlt(
		Program::BackBuffer(),
		(int)(rect->Left()),
		(int)(rect->Top()),
		(int)(rect->size.x),
		(int)(rect->size.y),
		memDC,
		frameSize.x * curFrame.x, frameSize.y * curFrame.y,
		frameSize.x, frameSize.y,
		transColor
	);
}

void Texture::Render(Rect* rect, RECT rectFrame)
{
	GdiTransparentBlt(
		Program::BackBuffer(),
		(int)(rect->Left()),
		(int)(rect->Right()),
		(int)(rect->size.x),
		(int)(rect->size.y),
		memDC,
		rectFrame.left, rectFrame.top,
		rectFrame.right, rectFrame.bottom,
		transColor
	);
}

void Texture::Render(Rect* rect, int alpha)
{
	// alpha : 0 ~ 255	(불투명도)
	blendFunc.SourceConstantAlpha = alpha;

	BitBlt(alphaMemDC,
		0, 0,
		frameSize.x, frameSize.y,
		Program::BackBuffer(),
		(int)(rect->Left()),
		(int)(rect->Right()),
		SRCCOPY
	);

	GdiTransparentBlt(
		alphaMemDC,
		0,0,
		originSize.x, originSize.y,
		memDC,
		0, 0,
		originSize.x, originSize.y,
		transColor
	);

	GdiAlphaBlend(
		Program::BackBuffer(),
		(int)(rect->Left()),
		(int)(rect->Right()),
		(int)(rect->size.x),
		(int)(rect->size.y),
		alphaMemDC,
		0, 0,
		frameSize.x, frameSize.y,
		blendFunc
	);
}

void Texture::Render(Rect* rect, POINT curFrame, int alpha)
{
	// alpha : 0 ~ 255	(불투명도)
	blendFunc.SourceConstantAlpha = alpha;

	BitBlt(alphaMemDC,
		frameSize.x * curFrame.x, frameSize.y * curFrame.y,
		frameSize.x, frameSize.y,
		Program::BackBuffer(),
		(int)(rect->Left()),
		(int)(rect->Right()),
		SRCCOPY
	);

	GdiTransparentBlt(
		alphaMemDC,
		0, 0,
		originSize.x, originSize.y,
		memDC,
		0, 0,
		originSize.x, originSize.y,
		transColor
	);

	GdiAlphaBlend(
		Program::BackBuffer(),
		(int)(rect->Left()),
		(int)(rect->Right()),
		(int)(rect->size.x),
		(int)(rect->size.y),
		alphaMemDC,
		frameSize.x * curFrame.x, frameSize.y * curFrame.y,
		frameSize.x, frameSize.y,
		blendFunc
	);
}
