#include "Framework.h"

Rect::Rect()
    : center(0, 0), size(0, 0)
{
	type = Type::RECT;
}

Rect::Rect(Vector2 center, Vector2 size)
    : center(center), size(size)
{
	type = Type::RECT;
}

Rect::Rect(float left, float top, float right, float bottom)
{
	type = Type::RECT;
	SetRect(left, top, right, bottom);
}

Rect::~Rect()
{
}

void Rect::Render(HDC hdc)
{
	if (!isActive)
		return;

	Rectangle(hdc,
		(int)Left(),
		(int)Top(),
		(int)Right(),
		(int)Bottom()
	);
}

bool Rect::IsCollision(Vector2 pos)
{
	if (!isActive)
		return false;
	if (pos.x > Left() && pos.x < Right())
	{
		if (pos.y > Top() && pos.y < Bottom())
		{
			return true;
		}
	}

    return false;
}

void Rect::SetRect(float left, float top, float right, float bottom)
{
	center.x = (left + right) * 0.5f;
	center.y = (top + bottom) * 0.5f;

	size.x = abs(right - left);
	size.y = abs(bottom - top);
}

bool Rect::IsCircleCollision(Circle* circle)
{
	if (!isActive)
		return false;
	//원이 네모의 상하좌우에 위치한 경우
	if ((circle->center.x > Left() && circle->center.x < Right() ||
		circle->center.y > Top() && circle->center.y < Bottom()))
	{
		Vector2 size = { circle->radius * 2, circle->radius * 2 };
		Rect temp(circle->center, size);

		if (IsRectCollision(&temp))
			return true;
	}
	else//대각선에 위치한 경우
	{
		Vector2 edges[4];
		edges[0] = { Left(), Top() };
		edges[1] = { Right(), Top() };
		edges[2] = { Left(), Bottom() };
		edges[3] = { Right(), Bottom() };

		for (Vector2 edge : edges)
			if (circle->IsCollision(edge))
				return true;
	}

	return false;
}

bool Rect::IsRectCollision(Rect* rect)
{
	if (!isActive)
		return false;
	if (rect->Left() < Right() && rect->Right() > Left())
	{
		if (rect->Top() < Bottom() && rect->Bottom() > Top())
		{
			return true;
		}
	}

	return false;
}

bool Rect::IsRectCollision(OUT Rect* overlap, IN Rect* rect)
{
	if (!isActive)
		return false;
	float left = max(rect->Left(), Left());
	float right = min(rect->Right(), Right());

	float top = max(rect->Top(), Top());
	float bottom = min(rect->Bottom(), Bottom());

	if (right - left > 0 && bottom - top > 0)
	{
		if (overlap != nullptr)
			overlap->SetRect(left, top, right, bottom);
		return true;
	}

	return false;
}
