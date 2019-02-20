#include "Character.h"

using namespace std;
Character::Character(sf::Vector2f scale, string charName, sf::Vector2f size) :Moveable(scale, size)
{	
	spriteCount = 8;
	texture = new sf::Texture[spriteCount];
	characterType = charName;

}

string Character::getCharacterType()
{
	return characterType;
}

bool Character::spawn(Map & map, int characterType, int& x, int& y)
{
	for (x; x < map.getMapRange().x; x++) {
		
		for (y; y < map.getMapRange().y; y++) {
			
			if (map.getFieldType(x, y) == characterType) {

				body->setPosition(x*map.size, y*map.size);
				nextPosition = body->getPosition();
				if (map.getFieldType(x, y) != 2) {
					map.setField(x, y, 0);
				}
				cout <<"type: "<<characterType<< " spawned!\n";
				return true;
			}
		}
		y = 0;
		
	}
	return false;
}

bool Character::loadTexture(string texturesDir)
{
	texturesDir += characterType + "/";
	sf::Image* img = new sf::Image();
	if (!img->loadFromFile(texturesDir + characterType + "SpriteSheet.PNG")) {
		std::cout << "Failed to load " + characterType + "SpriteSheet.PNG\n";
		return false;
	}
	for (int i = 0; i < spriteCount; i++)
	{
		if (!texture[i].loadFromImage(*img,
			sf::IntRect(i * size.x/body->getScale().x, 0,
				size.x / body->getScale().x, size.y / body->getScale().y)))
		{
			std::cout << "Failed to read " + std::to_string(i) + ". sprite from " + characterType + "SpriteSheet.PNG\n";
			return false;
		}
	}

	std::cout << "Textures loaded for: " << characterType;
	return true;
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
