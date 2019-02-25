#include "Moveable.h"

unsigned int Moveable::spriteCount = 1;

Moveable::Moveable(Vector2f scale, Vector2f size)
{
	body = new sf::Sprite;

	body->setScale(scale);
	nextPosition = body->getPosition();

	inAir = false;

	this->size = scale;
	this->size.x *= size.x;
	this->size.y *= size.y;

	velocity = sf::Vector2f(0, 0);
	maxVelocity = sf::Vector2f(10, -23);

	acceleration = 2;
	retardation = 0.5;
}


sf::FloatRect Moveable::getCurrentRect()
{
	return sf::FloatRect(body->getPosition().x, body->getPosition().y, size.x, size.y);
}

sf::FloatRect Moveable::getNextRect()
{
	return FloatRect(nextPosition, size);
}


Vector2f Moveable::getSize()
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

void Moveable::updateNextPosition(Map& map)
{
	updateNextPositionX(map.getLeftMoveLimit(getCurrentRect()), map.getRightMoveLimit(getCurrentRect()));
	updateNextPositionY(map.getUpMoveLimit(getCurrentRect()), map.getDownMoveLimit(getCurrentRect()));
}

void Moveable::updatePosition()
{
	body->setPosition(nextPosition);
}

void Moveable::updateNextPositionX(float leftBoundary, float rightBoundary)
{
	if (velocity.x > 0 && nextPosition.x + size.x + velocity.x >= rightBoundary) {
		nextPosition.x = rightBoundary - size.x;
		velocity.x = 0;

	}
	else if (velocity.x < 0 && nextPosition.x + velocity.x <= leftBoundary) {
		nextPosition.x = leftBoundary;
		velocity.x = 0;
	}
	nextPosition.x += velocity.x;

	if ((velocity.x < retardation && velocity.x > 0) || (velocity.x > -retardation && velocity.x < 0)) {
		velocity.x = 0;
	}

	//hamowanie
	if (velocity.x > 0) {
		velocity.x -= retardation;

	}
	else if (velocity.x < 0) {
		velocity.x += retardation;
	}

}

void Moveable::updateNextPositionY(float upBoundary, float downBoundary)
{
	if (velocity.y < 0 && nextPosition.y + velocity.y <= upBoundary) {
		nextPosition.y = upBoundary;
		velocity.y = 0;
	}

	if (nextPosition.y + size.y + velocity.y + GRAVITATION < downBoundary) {
		inAir = true;
		velocity.y = velocity.y + GRAVITATION;
	}
	else {
		velocity.y = 0;
		nextPosition.y = downBoundary - size.y;
		inAir = false;
	}

	nextPosition.y += velocity.y;
}


void Moveable::updateSpeed(sf::Vector2i & direction)
{
	if (velocity.x*direction.x < maxVelocity.x) {
		velocity.x += acceleration * direction.x;
	}
	if (velocity.x*direction.x > maxVelocity.x) {
		velocity.x = maxVelocity.x*direction.x;
	}
	if (direction.y > 0)
	{
		jump();
	}
}


void Moveable::jump()
{
	if (!inAir) {
		inAir = true;
		velocity.y = maxVelocity.y;
	}
}

//bool Moveable::loadTexture(string & texturesDir)
//{
//	sf::Image* img = new sf::Image();
//	if (!img->loadFromFile(texturesDir)) {
//		std::cout << "Failed to load " + texturesDir + "\n";
//		return false;
//	}
//	for (int i = 0; i < spriteCount; i++)
//	{
//		if (!texture[i].loadFromImage(*img,
//			sf::IntRect(i * size.x, 0, size.x, size.y)))
//		{
//			std::cout << "Failed to read " + std::to_string(i) + ". sprite from " + texturesDir + "\n";
//			return false;
//		}
//	}
//	return true;
//}

void Moveable::draw(RenderTarget& target, RenderStates states) const
{
	if(spriteCount != 0)body->setTexture(texture[0]);

	sf::Transform transform = getTransform();
	target.draw(*body, transform);
}
