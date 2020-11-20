#pragma once

class Camera
{
private:
	Rect* rect;
	float speed;

	Rect* mapRect;

	Rect* target;

	Vector2 offset;

	Vector2 destPos;

	Camera();
	~Camera();
public:
	static Camera* Get()
	{
		static Camera instance;
		return &instance;
	}

	void Update();

	void FreeMode();
	void FollowMode();

	Vector2 Pos();
	void SetPos(Vector2 value);
	Rect* GetMapRect() { return mapRect; }
	void SetTarget(Rect* value) { target = value; }
	void SetOffset(float x, float y) { offset = { x, y }; }
};