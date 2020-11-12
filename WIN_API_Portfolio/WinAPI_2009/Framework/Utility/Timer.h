#pragma once

class Timer
{
private:
	float timeScale;
	float timeElapsed;

	__int64 curTime;
	__int64 lastTime;
	__int64 periodFrequency;

	int frameRate;
	int frameCount;

	float oneSecCount;
	float runTime;

	float lockFPS;

	Timer();
	~Timer();

public:
	static Timer* Get()
	{
		static Timer instance;
		return &instance;
	}

	void Update();
	void Render(HDC hdc);

	void SetLockFPS(float value) { lockFPS = value; }

	int GetFPS() { return frameRate; }
	float GetElapsedTime() { return timeElapsed > 0.1f ? 0.1f : timeElapsed; }
	float GetRunTime() { return runTime; }
};