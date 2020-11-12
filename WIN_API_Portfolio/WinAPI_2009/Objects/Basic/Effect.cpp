#include "Framework.h"

Effect::Effect(Texture* texture, float speed)
	: ImageRect(texture)
{
	isActive = false;

	animation = new Animation(texture, speed);
	animation->SetDefault();
	animation->SetEndEvent(bind(&Effect::End, this));
}

Effect::~Effect()
{
	delete animation;
}

void Effect::Update()
{
	if (!isActive)
		return;
	animation->Update();
}

void Effect::Render()
{
	if (!isActive)
		return;
	ImageRect::Render(animation->GetFrame());
}

void Effect::Play(Vector2 pos)
{
	center = pos;
	isActive = true;
	animation->Play();
}

void Effect::End()
{
	isActive = false;
}
