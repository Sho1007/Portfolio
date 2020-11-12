#pragma once

class Piece : public ImageRect
{
private:
	POINT frame;

public:
	Piece(Texture* texture, Vector2 pos, POINT frame);
	~Piece();

	void Render();
};