#include "Framework.h"
#include "Cannon.h"

Cannon::Cannon()
	: angle(45), barrelLength(150), power(0), powerSpeed(3), moveSpeed(5)
{
	body = new Circle({ 200, 400 }, 100);
	barrel = new Line(body->center, Vector2(0, 0));

	angle = PI / 4;

	sm = new ShellManager();

	brushes[0] = CreateSolidBrush(RED);
	brushes[1] = CreateSolidBrush(YELLOW);

	powerFrontBar = new Rect(50, 500, 50, 550);
	powerBackBar = new Rect(50, 500, 700, 550);
}

Cannon::~Cannon()
{
	delete body;
	delete barrel;
	delete sm;

	delete powerFrontBar;
	delete powerBackBar;

	DeleteObject(brushes[0]);
	DeleteObject(brushes[1]);
}

void Cannon::Update()
{
	if (GetAsyncKeyState(VK_UP))
		angle += 0.1f;
	if (GetAsyncKeyState(VK_DOWN))
		angle -= 0.1f;

	if (KEY_PRESS(VK_RIGHT))
		body->center.x += moveSpeed;
	if (KEY_PRESS(VK_LEFT))
		body->center.x -= moveSpeed;

	barrel->start = body->center;

	if (KEY_DOWN(VK_SPACE))
	{
		power = 0;
	}

	if (KEY_PRESS(VK_SPACE))
	{
		power += powerSpeed;

		powerFrontBar->SetRect(powerFrontBar->Left(), powerFrontBar->Top(),
			powerFrontBar->Left() + power, powerFrontBar->Bottom());
	}

	if (KEY_UP(VK_SPACE))
	{
		sm->Fire(barrel->end, angle, power);
	}

	//Vector2 direction = mousePos - body->center;
	//angle = atan(-direction.y / direction.x);
	//angle = atan2(-direction.y, direction.x);

	barrel->end.x = cos(angle) * barrelLength;
	barrel->end.y = -sin(angle) * barrelLength;

	barrel->end += body->center;

	sm->Update();
}

void Cannon::Render(HDC hdc)
{
	body->Render(hdc);
	barrel->Render(hdc);

	sm->Render(hdc);

	oldBrush = (HBRUSH)SelectObject(hdc, brushes[1]);
	powerBackBar->Render(hdc);
	SelectObject(hdc, brushes[0]);
	powerFrontBar->Render(hdc);
	SelectObject(hdc, oldBrush);
}
