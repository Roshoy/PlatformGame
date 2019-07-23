#include "Player.h"



Player::Player(const sf::Vector2f& sscale, const sf::Vector2f& ssize) : Character(sscale, Character::CharacterType::Player, ssize)
{
	acceleration = 2.5;
	maxVelocity.x = 10;
	maxVelocity.y = 23;
	//maxVelocity.y = 14;
	retardation = 1;
	//body->setOrigin(1, 0);
	setAnimationSpeed(Idle, 20);
	setAnimationSpeed(Run, 50);
	setAnimationSpeed(Fall, 50);
}


Player::~Player()
{
}
