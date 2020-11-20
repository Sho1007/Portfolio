#include "Framework.h"

ImageRect::ImageRect()
	: texture(nullptr), frame{}
{
	size = { 0, 0 };
}

ImageRect::ImageRect(Texture* texture)
	: texture(texture), frame{}
{
	size = texture->GetSize();
}

ImageRect::ImageRect(Texture* texture, POINT frame)
	: texture(texture), frame(frame)
{
}

ImageRect::~ImageRect()
{	
}

void ImageRect::Render()
{
	if (!isActive)
		return;
	texture->Render(this, frame);
}

void ImageRect::Render(POINT curFrame)
{
	if (!isActive)
		return;
	texture->Render(this, curFrame);
}

void ImageRect::Render(int alpha)
{
	if (!isActive)
		return;
	texture->Render(this, alpha);
}

void ImageRect::Render(POINT curFrame, int alpha)
{
	if (!isActive)
		return;
	texture->Render(this, curFrame, alpha);
}

void ImageRect::BitRender(POINT curFrame)
{
	if (!isActive)
		return;
	texture->BitRender(this, curFrame);
}

void ImageRect::SetTexture(Texture* texture, POINT frame)
{
	this->texture = texture;
	this->frame = frame;
}

void ImageRect::CamRender()
{
	if (!isActive)
		return;

	Rect temp;
	temp.size = size;
	temp.center = center - CAM->Pos();
	
	texture->Render(&temp, frame);
}

void ImageRect::CamRender(POINT curFrame)
{
	if (!isActive)
		return;

	Rect temp;
	temp.size = size;
	temp.center = center - CAM->Pos();

	texture->Render(&temp, curFrame);
}
