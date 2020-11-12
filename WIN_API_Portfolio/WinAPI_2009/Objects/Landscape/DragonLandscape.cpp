#include "Framework.h"
#include "DragonLandscape.h"

DragonLandscape::DragonLandscape()
	: skySpeed(50.0f)
{
	CreateBG();
}

DragonLandscape::~DragonLandscape()
{
	for (ImageRect* s : sky)
	{
		delete s;
	}
}

void DragonLandscape::Update()
{
	for (ImageRect* s : sky)
	{
		s->center.y += skySpeed * DELTA;

		if (s->Top() > WIN_HEIGHT)
			s->center.y -= WIN_HEIGHT * 2.0f;
	}
}

void DragonLandscape::Render()
{
	for (ImageRect* s : sky)
	{
		s->Render();
	}
}

void DragonLandscape::CreateBG()
{
	Texture* skyTexture = TEXTURE->Add(L"Textures/HWShoot/bg1.bmp", 384, 512);

	sky[0] = new ImageRect(skyTexture);
	sky[0]->SetRect(0, 0, WIN_WIDTH, WIN_HEIGHT);
	sky[1] = new ImageRect(skyTexture);
	sky[1]->SetRect(0, WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT * 2.0f);
}
