#include "Framework.h"

HpBar::HpBar(Texture* back, Texture* front, float maxHp)
	: back(back), front(front), maxHp(maxHp), curHp(maxHp),
	target(nullptr), frontRect(nullptr)
{
	frontRect = new Rect();
}

HpBar::~HpBar()
{
}

void HpBar::Update()
{
	if (!(target == nullptr))
		center = target->center + offset - CAM->Pos();
	frontRect->SetRect(Left(), Top(), Left() + size.x * (curHp / maxHp), Bottom());
}

void HpBar::Render()
{
	back->Render(this);
	front->Render(frontRect);
}
