#pragma once

namespace GameMath
{
	enum class Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};

	int Random(int min, int max);
	float Random(float min, float max);

	string ToString(wstring value);
	wstring ToWString(string value);
}