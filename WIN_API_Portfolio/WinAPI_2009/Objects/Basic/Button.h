#pragma once

class Button : public Rect
{
private:
	enum State
	{
		UP,
		OVER,
		DOWN
	} state;

	Texture* up;
	Texture* over;
	Texture* down;

	int value;

	function<void()> Event;
	function<void(int)> EventParam;

	string text;
	HFONT font, oldFont;
	COLORREF fontColor, oldColor;
	int fontSize;
	POINT fontPos;

	bool isOver;
public:
	Button(Texture* up, Texture* over = nullptr, Texture* down = nullptr);
	Button(string text, Texture* up, Texture* over = nullptr, Texture* down = nullptr);
	~Button();

	void Update();
	void Render();

	void SetEvent(function<void()> value) { Event = value; }
	void SetEventParam(function<void(int)> value) { EventParam = value; }
	void SetValue(int value) { this->value = value; }
	void SetText(string value) { text = value; }
	void SetFontColor(COLORREF value) { fontColor = value; }
};