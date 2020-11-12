#include "Framework.h"
#include "Control.h"

//Control* Control::instance = nullptr;

Control::Control()
	: curState{}, oldState{}, mapState{}
{	
}

Control::~Control()
{
}

void Control::Update()
{
	memcpy(oldState, curState, sizeof(oldState));

	//0, 1 - 키보드 땟을 경우
	//128, 129 - 키보드를 눌렀을 경우
	GetKeyboardState(curState);

	for (int i = 0; i < KEYMAX; i++)
	{
		BYTE key = curState[i] & 0x80;
		curState[i] = key ? 1 : 0;

		int old = oldState[i];
		int cur = curState[i];

		if (old == 0 && cur == 1)
			mapState[i] = DOWN;
		else if (old == 1 && cur == 0)
			mapState[i] = UP;
		else if (old == 1 && cur == 1)
			mapState[i] = PRESS;
		else
			mapState[i] = NONE;
	}
}
