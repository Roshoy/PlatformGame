#pragma once
#include "Character.h"
class Fruk :
	public Character
{
public:
	Fruk(Vector2f sscale = Vector2f(2.f, 2.f), Vector2f ssize = Vector2f(27.f, 14.f));
	void updateNextPosition(Vector2f newPosition);
};

