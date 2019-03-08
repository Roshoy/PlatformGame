#include "Player.h"



Player::Player(Vector2f sscale, Vector2f ssize) : Character(sscale, Character::Player, ssize)
{
	acceleration = 2.5;
	maxVelocity.x = 10;
//	maxVelocity.y = 15;
	//maxVelocity.y = 14;
	retardation = 1;
	body->setOrigin(1, 0);
}


Player::~Player()
{
}
