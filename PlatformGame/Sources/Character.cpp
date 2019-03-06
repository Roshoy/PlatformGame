#include "Character.h"

using namespace std;

unsigned int Character::spriteCount = 8;
unsigned int Character::characterTypesCount = 2;

Character::Character(sf::Vector2f scale, CharacterType charName, sf::Vector2f size) :Moveable(scale, size)
{		
	characterType = charName;
}

Character::CharacterType Character::getCharacterType()
{
	return characterType;
}

void Character::spawn(Vector2f pos)
{
	body->setPosition(pos);
}

void Character::spawn(float x, float y)
{
	body->setPosition(x,y);
}


void Character::setTextures(sf::Texture * texture)
{
	this->texture = texture;
}


void Character::draw(RenderTarget& target, RenderStates states) const
{
	if (inAir) {
		if (velocity.x > 0) {
			body->setTexture(texture[JumpRight]);
			
		}
		else if(velocity.x < 0){
			body->setTexture(texture[JumpLeft]);
			
		}
		else{
			body->setTexture(texture[Jump]);
			
		}
	}
	else {
		
		if (velocity.x > 0) {
			if (int(body->getPosition().x) % 100 < 50) {
				body->setTexture(texture[Right1]);
				//cout << "4\n";
			}else{
				body->setTexture(texture[Right2]);
				
			}
		}
		else if (velocity.x < 0) {
			if (int(body->getPosition().x) % 100 < 50) {
				body->setTexture(texture[Left1]);
				//cout << "6\n";
			}
			else {
				body->setTexture(texture[Left2]);
				
			}
		}
		else {
			body->setTexture(texture[Idle]);
			
		}
	}
	
	sf::Transform transform = getTransform();
	target.draw(*body, transform);
}
