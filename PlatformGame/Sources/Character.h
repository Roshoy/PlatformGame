#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"
#include "Moveable.h"
#include "Animator.h"

#define GRAVITATION 1.5

using namespace std;

class Character : public Moveable, public Animator {
public:
	enum CharacterType
	{
		Player = 0,
		Fruk = 1
	};
	static unsigned int characterTypesCount;
	Character(const sf::Vector2f& scale = sf::Vector2f(0, 0),CharacterType charName = Player, const sf::Vector2f& size = sf::Vector2f(0,0));	

	CharacterType getCharacterType() const;
	virtual void setPosition(const sf::Vector2f& pos);
	void spawn(const sf::Vector2f& pos = sf::Vector2f(0,0));
	void updateNextPosition(const sf::Vector2f& newPosition) override;
	void updateTexture(bool right);
	void spawn(float x, float y);

	static unsigned int spriteCount;
	
protected:
	sf::RectangleShape hitbox;
	CharacterType characterType;
	void draw(RenderTarget& target, RenderStates states)const override;
};