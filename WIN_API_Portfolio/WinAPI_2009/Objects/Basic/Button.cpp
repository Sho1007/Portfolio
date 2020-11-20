#include "Framework.h"

Button::Button(Texture* up, Texture* over, Texture* down)
	: up(up), over(over), down(down), Event(nullptr), EventParam(nullptr), isOver(false), fontColor(WHITE), fontSize(0)
{
	size = up->GetSize();

	font = CreateFont(
		fontSize, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET, 100, 0, 0, 0, L"배달의민족 주아");

	fontPos.x = Left();
	fontPos.y = Top();
}

Button::Button(string text, Texture* up, Texture* over, Texture* down)
	: text(text), up(up), over(over), down(down), Event(nullptr), EventParam(nullptr), isOver(false), fontColor(RGB(150, 150, 150))
{
	size = up->GetSize();

	fontSize = size.x * 2.5f / text.length();

	font = CreateFont(
		fontSize, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET, 100, 0, 0, 0, L"배달의민족 주아");
}

Button::~Button()
{
	DeleteObject(font);
}

void Button::Update()
{
	fontPos.x = center.x - (fontSize * text.length() * 0.27f);
	fontPos.y = center.y - (fontSize * 0.5f);
	if (IsCollision(mousePos))
	{
		state = OVER;
		if (KEY_UP(VK_LBUTTON) && isOver)
		{
			if (Event != nullptr)
				Event();
			if (EventParam != nullptr)
				EventParam(value);
			isOver = false;
		}

		if (KEY_DOWN(VK_LBUTTON))
			isOver = true;
		if (KEY_PRESS(VK_LBUTTON))
			state = DOWN;
	}
	else
	{
		state = UP;

		if (KEY_UP(VK_LBUTTON))
			isOver = false;
	}
}

void Button::Render()
{
	switch (state)
	{
	case Button::UP:
		up->Render(this);
		fontColor = RGB(150, 150, 150);
		break;
	case Button::OVER:
		if (over != nullptr)
			over->Render(this);
		else
			up->Render(this);

		fontColor = RGB(255, 255, 255);
		break;
	case Button::DOWN:
		if (down != nullptr)
			down->Render(this);
		else
			up->Render(this);

		fontColor = RGB(150, 0, 0);
		break;
	}

	oldFont = (HFONT)SelectObject(Program::BackBuffer(), font);
	oldColor = (COLORREF)SetTextColor(Program::BackBuffer(), fontColor);
	TextOutA(Program::BackBuffer(), fontPos.x, fontPos.y, text.c_str(), text.length());
	SelectObject(Program::BackBuffer(), oldFont);
	SetTextColor(Program::BackBuffer(), oldColor);
}
