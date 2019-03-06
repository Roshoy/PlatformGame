#pragma once
#include "Character.h"
class Player :
	public Character
{
public:
	Player(Vector2f sscale = Vector2f(5.f, 5.f), Vector2f ssize = Vector2f(5.f, 10.f));
	~Player();
};

