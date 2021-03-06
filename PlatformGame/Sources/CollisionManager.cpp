#include "CollisionManager.h"
#include <valarray>

CollisionManager::CollisionManager(Player& player, std::list<Character*>& enemies, Map& map)
{
	this->player = &player;
	std::cout << &player << std::endl;
	std::cout << &this->player << std::endl;
	this->enemies = &enemies;
	this->map = &map;
}

bool CollisionManager::collisionWillBeBetweenCharacters(Character & objA, Character & objB)
{
	sf::FloatRect objARect = objA.getNextRect();
	sf::FloatRect objBRect = objB.getNextRect();
	return objARect.intersects(objBRect);
}

CollisionManager::CollisionResult CollisionManager::collisionBetweenCharactersOutcome(Character & objA, Character & objB)
{
	if(!collisionWillBeBetweenCharacters(objA,objB))
	{
		return Nothing;
	}
	if(objA.getCharacterType() == Character::Player)
	{
		if(objA.getCurrentRect().height + objA.getCurrentRect().top < objB.getCurrentRect().top)
		{
			return BDies;
		}
		
		return ADies;
	}	
	return Nothing;
}

CollisionManager::CollisionResult CollisionManager::playerCollisionWithEnemies()
{
	std::list<Character*>::iterator iter = enemies->begin();
	while(iter != enemies->end())
	{
		CollisionResult b = collisionBetweenCharactersOutcome(*player, **iter);
		switch (b)
		{
		case ADies:
			return ADies;
		case BDies:
			enemies->erase(iter++);
			break;
		case Nothing:
			iter++;
			break;
		}
	}
	return Nothing;
}

sf::Vector2f CollisionManager::characterCollisionWithMap(Rect<float> currentRect, Rect<float> lastRect)
{
	int dx = lastRect.left - currentRect.left;
	if(dx > 0)
	{
		float boundary = getRightMoveLimit(currentRect,dx);
		lastRect.left = min(lastRect.left, boundary - lastRect.width);
	}else if(dx < 0)
	{
		float boundary = getLeftMoveLimit(currentRect, dx);
		lastRect.left = max(lastRect.left, boundary);
	}
	currentRect.left = lastRect.left;
	int dy = lastRect.top - currentRect.top;
	if (dy > 0)
	{
		float boundary = getDownMoveLimit(currentRect, dy);
		lastRect.top = min(lastRect.top, boundary - lastRect.height);
	}
	else if (dy < 0)
	{
		float boundary = getUpMoveLimit(currentRect, dy);
		lastRect.top = max(lastRect.top, boundary);
	}
	
	return {lastRect.left,lastRect.top};
}

bool CollisionManager::rectCollisionWithMap(Rect<float> currentRect)
{
	for(int x=currentRect.left/Field::fieldSize;
		x<=(currentRect.left+currentRect.width) / Field::fieldSize ;
		x++)
	{
		for (int y = currentRect.top / Field::fieldSize;
			y <= (currentRect.top + currentRect.height) / Field::fieldSize ;
			y++)
		{			
			if(map->getField(x,y).isSolid()){ return true; }
		}
	}
	return false;
}

float CollisionManager::getUpMoveLimit(FloatRect character, float dy)
{
	int L = int(character.left / Field::fieldSize);
	int P = int((character.left + character.width) / Field::fieldSize);
	int y = int(character.top / Field::fieldSize);// -1;
	if (P*Field::fieldSize == character.left + character.width) { P--; }
	int minY = int((character.top + dy) / Field::fieldSize);
	for (;y<Map::mapDimensions.y && y >= 0 && y >= minY; y--)
	if (y >= 0) {
		for (int x = L; x <= P && x >= 0; x++) {
			if (map->getField(x, y).isSolid()) {
				return (y + 1)*Field::fieldSize;
			}
		}
	}
	return 0;
}

float CollisionManager::getRightMoveLimit(FloatRect character, float dx)
{
	int L = int(character.top / Field::fieldSize);
	int P = int((character.top + character.height) / Field::fieldSize);
	int x = int((character.left + character.width) / Field::fieldSize);
	int maxX = (character.width + (character.left + dx)) / Field::fieldSize+1;
	if (P*Field::fieldSize == character.top + character.height) { P--; }
	for (;x >= 0 && x < Map::mapDimensions.x && x <= maxX; x++) {
		for (int y = L; y <= P && y >= 0; y++) {
			
			if (map->getField(x, y).isSolid()) { return (x)*Field::fieldSize;}
		}
	}
	
	return Field::fieldSize * Map::mapDimensions.x;
}

float CollisionManager::getDownMoveLimit(FloatRect character, float dy)
{
	int L = int(character.left / Field::fieldSize);
	int P = int((character.left + character.width) / Field::fieldSize);
	int y = int((character.top + character.height) / Field::fieldSize);
	if (P*Field::fieldSize == character.left + character.width) { P--; }
	int maxY = (character.height + (character.top + dy)) / Field::fieldSize;
	for (;y >= 0 && y < Map::mapDimensions.y && y <= maxY; y++) {
		for (int x = L; x <= P && x >= 0; x++) {
			if (map->getField(x, y).isSolid()) {				
				return y * Field::fieldSize;
			}
		}
	}	
	return Map::mapDimensions.y*Field::fieldSize;
}

float CollisionManager::getLeftMoveLimit(FloatRect character, float dx)
{
	int L = int(character.top / Field::fieldSize);
	int P = int((character.top + character.height) / Field::fieldSize);
	int x = int((character.left) / Field::fieldSize);
	if (P*Field::fieldSize == character.top + character.height) { P--; }
	int minX = (character.width + dx) / Field::fieldSize;
	for (;x<Map::mapDimensions.x && x >= 0 && x >= minX;x--) {
		for (int y = L; y <= P && y >= 0; y++) {
			if (map->getField(x, y).isSolid()) {
				return (x + 1)*Field::fieldSize;
			}
		}
	}
	return 0;
}