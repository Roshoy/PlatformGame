#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"
#include "Moveable.h"

#define GRAVITATION 1.5

using namespace sf;
using namespace std;

class Character : public Moveable {
public:
	enum CharacterType
	{
		Player = 0,
		Fruk = 1
	};
	static unsigned int characterTypesCount;
	Character(Vector2f scale = Vector2f(0, 0),CharacterType charName = Player, Vector2f size = Vector2f(0,0));	

	CharacterType getCharacterType();

	void spawn(sf::Vector2f pos = sf::Vector2f(0,0));

	void spawn(float x, float y);

	enum SpriteState {Idle      = 0,
					  Jump      = 1,
					  JumpLeft  = 2,
					  JumpRight = 3,
					  Left1     = 4,
					  Left2     = 5,
					  Right1    = 6,
					  Right2    = 7};
	bool loadTexture(std::string texturesDir);
	void setTextures(sf::Texture* texture);
	static unsigned int spriteCount;
	
protected:

	CharacterType characterType;
	void draw(RenderTarget& target, RenderStates states)const override;
};