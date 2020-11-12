#pragma once

class Line
{
public:
	Vector2 start;
	Vector2 end;

	Line(Vector2 start, Vector2 end);

	void Render(HDC hdc);

	bool IsBetween(Line* line);
};