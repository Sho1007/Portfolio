#pragma once

class Tile : public ImageRect
{
	int type;
public:
	Tile();
	Tile(Texture* texture, POINT frame);
	~Tile();
};