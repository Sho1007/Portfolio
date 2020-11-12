#include "Framework.h"

Object::Object() : isActive(true)
{
}

bool Object::IsCollision(Object* object)
{
	switch (object->type)
	{
	case Type::CIRCLE:
		return IsCircleCollision((Circle*)object);
		break;
	case Type::RECT:
		return IsRectCollision((Rect*)object);
		break;	
	}

    return false;
}