#include "Fruk.h"
#include <iostream>

Fruk::Fruk(const sf::Vector2f& sscale, const sf::Vector2f& ssize):Character(sscale, Character::CharacterType::Fruk, ssize)
{
	maxVelocity.x = 3;
	velocity.x = 2;
	retardation = 1;
	acceleration = 2.5;
	setAnimationSpeed(Idle, 20);
	setAnimationSpeed(Run, 40);
	std::cout << "Enemy spawned\n";
}

void Fruk::updateNextPosition(const sf::Vector2f& newPosition)
{
	//cout << "x: " << getCurrentRect().left << " y: " << getCurrentRect().top << endl;
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
	hitbox.setPosition(getCurrentRect().left, getCurrentRect().top);
	updateTexture(false);
}
