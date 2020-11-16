#pragma once

class ImageRect : public Rect
{
protected:
	Texture* texture;
	POINT frame;

public:
	ImageRect();
	ImageRect(Texture* texture);
	ImageRect(Texture* texture, POINT frame);
	~ImageRect();

	void Render();
	void Render(POINT curFrame);
	void Render(int alpha);
	void Render(POINT curFrame, int alpha);
	void BitRender(POINT curFrame);

	POINT GetFrame() { return frame; }

	void SetTexture(Texture* texture, POINT frame = { 0, 0 });

	void CamRender();
};