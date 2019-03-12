#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"
#include "Moveable.h"
#include "Animator.h"

#define GRAVITATION 1.5

using namespace sf;
using namespace std;

class Character : public Moveable, public Animator {
public:
	enum CharacterType
	{
		Player = 0,
		Fruk = 1
	};
	static unsigned int characterTypesCount;
	Character(Vector2f scale = Vector2f(0, 0),CharacterType charName = Player, Vector2f size = Vector2f(0,0));	

	CharacterType getCharacterType();
	virtual void setPosition(sf::Vector2f pos);
	void spawn(sf::Vector2f pos = sf::Vector2f(0,0));
	void updateNextPosition(sf::Vector2f newPosition) override;
	void updateTexture(bool right);
	void spawn(float x, float y);

	static unsigned int spriteCount;
	
protected:

	CharacterType characterType;
	void draw(RenderTarget& target, RenderStates states)const override;
};