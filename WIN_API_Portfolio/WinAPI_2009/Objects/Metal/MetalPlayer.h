#pragma once

class MetalPlayer : public ImageRect
{
	float speed;
	float attack;
	float bombCount;
public:
	MetalPlayer();
	~MetalPlayer();
};