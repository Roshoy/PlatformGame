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

bool Character::spawn(Map & map, int characterType, int& x, int& y)
{
	for (auto it = map.fields.begin(); it != map.fields.end(); ++it) {
		if (it->second->getType() == characterType) {
			body->setPosition(x*map.scale, y*map.scale);
			nextPosition = body->getPosition();

			cout << "type: " << characterType << " spawned!\n";
			return true;
		}
	}

	for (x; x < map.getMapRange().x; x++) {
		
		for (y; y < map.getMapRange().y; y++) {
			
			if (map.getFieldType(x, y) == characterType) {

				body->setPosition(x*map.scale, y*map.scale);
				nextPosition = body->getPosition();
				
				cout <<"type: "<<characterType<< " spawned!\n";
				return true;
			}
		}
		y = 0;
		
	}
	return false;
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
			}else{
				body->setTexture(texture[Right2]);
			}
		}
		else if (velocity.x < 0) {
			if (int(body->getPosition().x) % 100 < 50) {
				body->setTexture(texture[Left1]);
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
