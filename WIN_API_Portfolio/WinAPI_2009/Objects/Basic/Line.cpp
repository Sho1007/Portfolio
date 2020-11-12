#include "Framework.h"

Line::Line(Vector2 start, Vector2 end)
	: start(start), end(end)
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc, (int)start.x, (int)start.y, nullptr);
	LineTo(hdc, (int)end.x, (int)end.y);
}

bool Line::IsBetween(Line* line)
{
	Vector2 A = line->end - start;
	Vector2 B = line->start - start;
	Vector2 C = end - start;

	float crossA = C.Cross(A);
	float crossB = C.Cross(B);

	return crossA * crossB < 0;
}
