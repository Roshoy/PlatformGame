#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"
#include "Moveable.h"

#define GRAVITATION 1.5

using namespace sf;
using namespace std;

class Character : public Moveable {
public:
	Character(Vector2f scale = Vector2f(0, 0),string charName = "", Vector2f size = Vector2f(0,0));	

	string getCharacterType();

	bool spawn(Map& map, int type, int& xInit, int& yInit);

	enum SpriteState {Idle      = 0,
					  Jump      = 1,
					  JumpLeft  = 2,
					  JumpRight = 3,
					  Left1     = 4,
					  Left2     = 5,
					  Right1    = 6,
					  Right2    = 7};
	bool loadTexture(std::string texturesDir);
protected:

	string characterType;
	void draw(RenderTarget& target, RenderStates states)const override;
};