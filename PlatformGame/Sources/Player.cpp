#include "Player.h"



Player::Player(Vector2f sscale, Vector2f ssize) : Character(sscale, "Player", ssize)
{
	acceleration = 2.5;
	maxVelocity.x = 8;
	retardation = 1;

}


Player::~Player()
{
}
