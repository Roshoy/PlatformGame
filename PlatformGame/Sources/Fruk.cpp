#include "Fruk.h"

Fruk::Fruk(Vector2f sscale, Vector2f ssize):Character(sscale, Character::Fruk, ssize)
{
	maxVelocity.x = 6;
	retardation = 1;
	acceleration = 2.5;
}

void Fruk::updateNextPosition(Vector2f newPosition)
{
	if (newPosition.x != nextPosition.x)
	{
		velocity.x *= -1;
	}
	if (newPosition.y != nextPosition.y)
	{
		inAir = false;
		velocity.y = 0;
	}
	nextPosition = newPosition;
}
