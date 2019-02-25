#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"

#define GRAVITATION 1.5

class Moveable: public Drawable, public Transformable
{
public:
	Moveable(Vector2f sscale = sf::Vector2f(0, 0), Vector2f ssize = sf::Vector2f(0, 0));
	sf::FloatRect getCurrentRect();
	sf::FloatRect getNextRect();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	sf::Vector2f getMaxSpeed();
	sf::Vector2f getSpeed();

	void setPosition(sf::Vector2f pos);

	void updateNextPosition(Map& map);
	void updatePosition();

	void updateSpeed(sf::Vector2i & direction);
	//void calculateNextPosition();
	void jump();

	bool loadTexture(std::string & texturesDir);
	static unsigned int spriteCount;

protected:

	void updateNextPositionX(float leftBoundary, float rightBoundary);
	void updateNextPositionY(float upBoundary, float downBoundary);

	Sprite* body;
	Vector2f size;
	Texture* texture;

	sf::Vector2f nextPosition;

	sf::Vector2f velocity;
	sf::Vector2f maxVelocity;
	float acceleration;
	float retardation;

	bool inAir;
	
	void draw(RenderTarget& target, RenderStates states)const override;
};