#pragma once
#include "Character.h"
class Fruk :
	public Character
{
public:
	Fruk(Vector2f sscale = Vector2f(5.f, 5.f), Vector2f ssize = Vector2f(8.f, 10.f));
	void updateNextPosition(Vector2f newPosition);
};

