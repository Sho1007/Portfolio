#pragma once

class Animation
{
private:
	vector<POINT> frames;
	vector<int> action;

	vector<RECT> rectFrames;

	int curPlayNum;

	POINT maxFrame;

	bool play;
	bool loop;
	bool pingpong;

	float time;
	float frameUpdateTime;

	function<void()> EndEvent;
public:	
	Animation(Texture* texture, float frameUpdateTime = 0.1f);
	~Animation();

	void Update();

	void SetDefault(bool loop = false, bool pingpong = false);
	void SetArray(int* arr, int arrSize, 
		bool loop = false, bool pingpong = false);
	void SetPart(int start, int end, bool loop = false, bool pingpong = false);
	void SetRectFrame(RECT rect);

	void SetPingpong();

	void Play() { play = true, curPlayNum = 0; }
	void Stop() { play = false; }

	bool GetPlay() { return play; }

	POINT GetFrame() { return frames[action[curPlayNum]]; }
	RECT GetRectFrame() { return rectFrames[curPlayNum]; }

	void SetEndEvent(function<void()> Event) { EndEvent = Event; }

	void Loop(bool value) { loop = value; }
	void PingPong(bool value) { pingpong = value; }
};