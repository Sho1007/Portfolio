#include "Framework.h"

Tile::Tile()
	: ImageRect(), type(0)
{
}

Tile::Tile(Texture* texture, POINT frame)
	: ImageRect(texture, frame), type(0)
{
}

Tile::~Tile()
{
}
