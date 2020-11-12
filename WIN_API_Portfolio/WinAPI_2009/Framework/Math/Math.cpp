#include "Framework.h"
#include "Math.h"

int GameMath::Random(int min, int max)
{
    return rand() % (max - min) + min;
}

float GameMath::Random(float min, float max)
{
    float normal = (float)rand() / (float)RAND_MAX;

    return min + (max - min) * normal;
}

string GameMath::ToString(wstring value)
{
	string temp;
	temp.assign(value.begin(), value.end());
	return temp;
}

wstring GameMath::ToWString(string value)
{
	wstring temp;
	temp.assign(value.begin(), value.end());

	return temp;
}
