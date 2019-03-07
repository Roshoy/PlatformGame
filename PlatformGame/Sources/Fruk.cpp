#include "Fruk.h"

Fruk::Fruk(Vector2f sscale, Vector2f ssize):Character(sscale, Character::Fruk, ssize)
{
	maxVelocity.x = 10;
	velocity.x = 0;
	retardation = 1;
	acceleration = 2.5;
	cout << "Enemy spawned\n";
}

void Fruk::updateNextPosition(Vector2f newPosition)
{
	
	if (newPosition.x != nextPosition.x)
	{
		velocity.x *= -1;
	}
	
	if (newPosition.y != nextPosition.y) {
		velocity.y = 0;
		if (newPosition.y < nextPosition.y && newPosition.y >= 0)
		{
			inAir = false;
		}
	}
	nextPosition = newPosition;
}
