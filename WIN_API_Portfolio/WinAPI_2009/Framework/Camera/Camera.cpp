#include "Framework.h"

Camera::Camera()
	: speed(300.0f), target(nullptr), offset(CENTER_X, CENTER_Y)
{
	rect = new Rect(0, 0, WIN_WIDTH, WIN_HEIGHT);
	mapRect = new Rect(0, 0, WIN_WIDTH, WIN_HEIGHT);
}

Camera::~Camera()
{
	delete rect;
	delete mapRect;
}

void Camera::Update()
{
	if (target != nullptr)
		FollowMode();
	else
		FreeMode();
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('A'))
		{
			rect->center.x -= speed * DELTA;

			if (rect->center.x < mapRect->Left())
			{
				rect->center.x = mapRect->Left();
			}
		}
		if (KEY_PRESS('D'))
		{
			rect->center.x += speed * DELTA;
			if (rect->center.x > mapRect->Right() - rect->size.x)
			{
				rect->center.x = mapRect->Right() - rect->size.x;
			}
		}
		if (KEY_PRESS('W'))
		{
			rect->center.y -= speed * DELTA;
			if (rect->center.y < mapRect->Top())
			{
				rect->center.y = mapRect->Top();
			}
		}
		if (KEY_PRESS('S'))
		{
			rect->center.y += speed * DELTA;
			if (rect->center.y > mapRect->Bottom() - rect->size.y)
			{
				rect->center.y = mapRect->Bottom() - rect->size.y;
			}
		}
	}
}

void Camera::FollowMode()
{
	destPos = target->center - offset;
	
	if (destPos.x < mapRect->Left())
	{
		destPos.x = mapRect->Left();
	}
	else if (destPos.x > mapRect->Right() - rect->size.x)
	{
		destPos.x = mapRect->Right() - rect->size.x;
	}
	
	if (destPos.y < mapRect->Top())
	{
		destPos.y = mapRect->Top();
	} else if (destPos.y > mapRect->Bottom() - rect->size.y)
	{
		destPos.y = mapRect->Bottom() - rect->size.y;
	}
	
	rect->center = LERP(rect->center, destPos, DELTA);
}

Vector2 Camera::Pos()
{
	return rect->center;
}

void Camera::SetPos(Vector2 value)
{
	rect->center = value;
}
