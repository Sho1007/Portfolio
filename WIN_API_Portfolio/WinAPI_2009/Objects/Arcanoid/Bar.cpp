#include "Framework.h"
#include "Bar.h"

Bar::Bar() : speed(300)
{
	center = { CENTER_X, WIN_HEIGHT * 0.9f };
	size = { 200, 30 };

	brush = CreateSolidBrush(RGB(100, 100, 100));
}

Bar::~Bar()
{
	DeleteObject(brush);
}

void Bar::Update()
{
	if (KEY_PRESS(VK_RIGHT))
	{
		center.x += speed * DELTA;
		if (Right() > WIN_WIDTH)
			center.x = WIN_WIDTH - Half().x;
	}
	if (KEY_PRESS(VK_LEFT))
	{
		center.x -= speed * DELTA;
		if (Left() < 0)
			center.x = Half().x;
	}
}

void Bar::Render(HDC hdc)
{
	SelectObject(hdc, brush);
	Rect::Render(hdc);
}
