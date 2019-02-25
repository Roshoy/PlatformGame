#include "Fruk.h"

Fruk::Fruk(Vector2f sscale, Vector2f ssize):Character(sscale, Character::Fruk, ssize)
{
	maxVelocity.x = 6;
	retardation = 1;
	acceleration = 2.5;
}
