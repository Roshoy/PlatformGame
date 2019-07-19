#pragma once
#include "Character.h"
class Player :
	public Character
{
public:
	Player(const sf::Vector2f& sscale = sf::Vector2f(2.f, 2.f), const sf::Vector2f& ssize = sf::Vector2f(19.f, 29.f));
	~Player();
};

