#include "Framework.h"

Animation::Animation(Texture* texture, float frameUpdateTime)
	: frameUpdateTime(frameUpdateTime), time(0), play(false),
	loop(false), pingpong(false), EndEvent(nullptr)
{
	maxFrame = texture->GetMaxFrame();

	for (int y = 0; y < maxFrame.y; y++)
	{
		for (int x = 0; x < maxFrame.x; x++)
		{
			frames.emplace_back(POINT{ x, y });
		}
	}
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (!play)
		return;

	time += DELTA;

	if (time > frameUpdateTime)
	{
		time -= frameUpdateTime;
		curPlayNum++;

		if (curPlayNum > action.size() - 1)
		{
			if (loop)
			{
				curPlayNum = 0;
			}
			else
			{
				curPlayNum--;
				play = false;

				if (EndEvent != nullptr)
					EndEvent();
			}
		}
	}
}

void Animation::SetDefault(bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (UINT i = 0; i < frames.size(); i++)
	{
		action.emplace_back(i);
	}

	SetPingpong();
}

void Animation::SetArray(int* arr, int arrSize, bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (UINT i = 0; i < arrSize; i++)
	{
		action.emplace_back(arr[i]);
	}

	SetPingpong();
}

void Animation::SetPart(int start, int end, bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (UINT i = start; i <= end; i++)
	{
		action.emplace_back(i);
	}

	SetPingpong();
}

void Animation::SetRectFrame(RECT value)
{
	RECT rect = value;
	rectFrames.emplace_back(rect);
	action.emplace_back(action.size());
}

void Animation::SetPingpong()
{
	if (!pingpong)
		return;

	for (int i = action.size() - 2; i >= 0; i--)
	{
		action.emplace_back(action[i]);
	}
}
