#pragma once
#include "Character.h"
class Player :
	public Character
{
public:
	Player(Vector2f sscale = Vector2f(2.f, 2.f), Vector2f ssize = Vector2f(19.f, 29.f));
	~Player();
};

