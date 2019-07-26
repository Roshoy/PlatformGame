#pragma once
#include "Character.h"
class Fruk :
	public Character
{
public:
	Fruk(const sf::Vector2f& sscale = sf::Vector2f(2.f, 2.f), const sf::Vector2f& ssize = sf::Vector2f(27.f, 14.f));
	void updateNextPosition(const sf::Vector2f& newPosition) override;
};

