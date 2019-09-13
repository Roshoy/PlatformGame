#include "Fruk.h"
#include <iostream>

Fruk::Fruk(const sf::Vector2f& sscale, const sf::Vector2f& ssize):Character(sscale, Character::CharacterType::Fruk, ssize)
{
	_maxVelocity.x = 3;
	_velocity.x = 2;
	_retardation = 1;
	_acceleration = 2.5;
	setAnimationSpeed(State::Idle, 20);
	setAnimationSpeed(State::Run, 40);
	std::cout << "Enemy spawned\n";
}

void Fruk::updateNextPosition(const sf::Vector2f& newPosition)
{
	//cout << "x: " << getCurrentRect().left << " y: " << getCurrentRect().top << endl;
	if (newPosition.x != _nextPosition.x)
	{
		_velocity.x *= -1;
	}
	
	if (newPosition.y != _nextPosition.y) {
		_velocity.y = 0;
		if (newPosition.y < _nextPosition.y && newPosition.y >= 0)
		{
			_inAir = false;
		}
	}
	_nextPosition = newPosition;
	_hitbox.setPosition(getCurrentRect().left, getCurrentRect().top);
	updateTexture(false);
}
