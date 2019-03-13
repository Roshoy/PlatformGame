#pragma once
#include <SFML\Graphics.hpp>

#define GRAVITATION 1.5

class Moveable: public sf::Drawable, public sf::Transformable
{
public:
	Moveable(sf::Vector2f sscale = sf::Vector2f(0, 0), sf::Vector2f ssize = sf::Vector2f(0, 0));
	sf::FloatRect getCurrentRect();
	sf::FloatRect getNextRect();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	sf::Vector2f getMaxSpeed();
	sf::Vector2f getMaxAcceleration();
	sf::Vector2f getSpeed();
	bool isInAir() { return inAir; }
	virtual void setPosition(sf::Vector2f pos);

	virtual void updateNextPosition(sf::Vector2f newPosition);
	void updatePosition();

	virtual void updateSpeed(sf::Vector2i & direction);
	void jump();
protected:

	sf::Sprite* body;
	sf::Vector2f size;
	sf::Vector2f scale;
	bool inAir;
	sf::Vector2f nextPosition;
	sf::Vector2f velocity;
	sf::Vector2f maxVelocity;
	float acceleration;
	float retardation;	
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};