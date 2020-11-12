#pragma once

class HpBar : public Rect
{
private:
	Texture* back;
	Texture* front;

	float maxHp;
	float curHp;

	Rect* target;
	Vector2 offset;

	Rect* frontRect;
public:
	HpBar(Texture* back, Texture* front, float maxHp);
	~HpBar();

	void Update();
	void Render();

	void SetHp(float hp) { 
		maxHp = hp;
		curHp = hp;
	}
	void Damage(float damage) { 
		curHp -= damage;
		curHp = max(0, curHp);
	}
	void SetTarget(Rect* value) { target = value; }
	void SetOffset(Vector2 value) { offset = value; }
	float GetHp() { return curHp; }
};