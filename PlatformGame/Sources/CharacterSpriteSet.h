#pragma once
#include <SFML/Graphics.hpp>

class CharacterSpriteSet {
public:
	enum SpriteState {
		Idle = 0,
		Jump = 1,
		JumpLeft = 2,
		JumpRight = 3,
		Left1 = 4,
		Left2 = 5,
		Right1 = 6,
		Right2 = 7
	};
	CharacterSpriteSet();
	void setTexture(SpriteState state, sf::Texture & tex);

private:
	sf::Texture* texture;
};