#include "Moveable.h"
#include "Animator.h"
#include <iostream>

Moveable::Moveable(sf::Vector2f scale, sf::Vector2f size)
{
	body = new sf::Sprite;

	body->setScale(scale);
	nextPosition = body->getPosition();

	inAir = true;

	this->size = scale;
	this->size.x *= size.x;
	this->size.y *= size.y;

	velocity = sf::Vector2f(0, 0);
	maxVelocity = sf::Vector2f(10, 23);

	acceleration = 2;
	retardation = 0.5;
}


sf::FloatRect Moveable::getCurrentRect()
{
	return sf::FloatRect(body->getPosition().x, body->getPosition().y, size.x, size.y);
}

sf::FloatRect Moveable::getNextRect()
{
	return sf::FloatRect(nextPosition, size);
}


sf::Vector2f Moveable::getSize()
{
	return size;
}

sf::Vector2f Moveable::getPosition()
{
	return body->getPosition();
}

sf::Vector2f Moveable::getMaxSpeed()
{
	return maxVelocity;
}

sf::Vector2f Moveable::getSpeed()
{
	return velocity;
}

void Moveable::setPosition(sf::Vector2f pos)
{
	body->setPosition(pos);
	nextPosition = pos;
}

void Moveable::updateNextPosition(sf::Vector2f newPosition)
{
	std::cout << "Still works\n";
	if(newPosition.x != nextPosition.x)
	{
		velocity.x = 0;
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

void Moveable::updatePosition()
{	
	body->setPosition(nextPosition);
}

void Moveable::updateSpeed(sf::Vector2i & direction)
{
	if (velocity.x*direction.x < maxVelocity.x) {
		velocity.x += acceleration * direction.x;
	}
	if (velocity.x*direction.x > maxVelocity.x) {
		velocity.x = maxVelocity.x*direction.x;
	}
	if (velocity.x >= retardation) {
		velocity.x -= retardation;
	}
	else if (velocity.x <= -retardation) {
		velocity.x += retardation;
	}
	else
	{
		velocity.x = 0;
	}
	velocity.y += GRAVITATION;
	if (velocity.y > maxVelocity.y)velocity.y = maxVelocity.y;
	if (velocity.y < -maxVelocity.y)velocity.y = -maxVelocity.y;
		
	if (direction.y < 0){ jump();}

	nextPosition += velocity;
}


void Moveable::jump()
{
	if (!inAir) {		
		inAir = true;
		velocity.y = -maxVelocity.y;
	}
}

void Moveable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Transform transform = getTransform();
	target.draw(*body, transform);
}
