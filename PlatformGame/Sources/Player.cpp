#include "Player.h"

Player::Player(const sf::Vector2f& sscale, const sf::Vector2f& ssize) : Character(sscale, Character::CharacterType::Player, ssize)
{
	_acceleration = 2.5;
	_maxVelocity.x = 10;
	_maxVelocity.y = 23;
	//_maxVelocity.y = 14;
	_retardation = 1;
	//_body->setOrigin(1, 0);
	setAnimationSpeed(State::Idle, 20);
	setAnimationSpeed(State::Run, 50);
	setAnimationSpeed(State::Fall, 50);
}

Player::~Player()
{
}
