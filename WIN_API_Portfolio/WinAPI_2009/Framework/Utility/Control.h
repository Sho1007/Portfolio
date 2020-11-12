#pragma once

#define KEYMAX 255

class Control
{
private:
	enum {
		NONE,
		DOWN,
		UP,
		PRESS
	};

	BYTE curState[KEYMAX];
	BYTE oldState[KEYMAX];
	BYTE mapState[KEYMAX];

	//static Control* instance;

	Control();
	~Control();
public:
	static Control* Get()
	{
		static Control instance;
		return &instance;
	}
	/*
	static Control* Get()
	{
		if (instance == nullptr)
			instance = new Control();

		return instance;
	}*/

	//static void Delete() { delete instance; }

	void Update();

	bool Down(UINT key) { return mapState[key] == DOWN; }
	bool Up(UINT key) { return mapState[key] == UP; }
	bool Press(UINT key) { return mapState[key] == PRESS; }
};