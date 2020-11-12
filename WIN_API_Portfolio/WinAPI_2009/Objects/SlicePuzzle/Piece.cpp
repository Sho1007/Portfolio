#include "Framework.h"
#include "Piece.h"

Piece::Piece(Texture* texture, Vector2 pos, POINT frame)
	: ImageRect(texture), frame(frame)
{
	center = pos;
	size = texture->GetSize();
}

Piece::~Piece()
{
}

void Piece::Render()
{
	ImageRect::Render(frame);
}
