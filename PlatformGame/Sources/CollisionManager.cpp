#include "CollisionManager.h"

CollisionManager::CollisionManager()
= default;

CollisionManager::CollisionManager(Player& player, std::list<Character>& enemies)
{
	this->player = &player;
	std::cout << &player << std::endl;
	std::cout << &this->player << std::endl;
	this->enemies = &enemies;
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::setTestString(std::string* str)
{
	testString = str;
}

bool CollisionManager::collisionWillBeBetweenCharacters(Character & objA, Character & objB)
{
	sf::FloatRect objARect = objA.getNextRect();
	sf::FloatRect objBRect = objB.getNextRect();
	return objARect.intersects(objBRect);
}

CollisionManager::CollisionResult CollisionManager::collisionOutcome(Character & objA, Character & objB)
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
	//std::cout<<*testString<<'\n';
	for (std::list<Character>::iterator iter = enemies->begin(); iter != enemies->end(); ++iter)
	{
		switch (collisionOutcome(*player, *iter))
		{
		case ADies:
			return ADies;
		case BDies:
			enemies->erase(iter++);
			--iter;
			break;
		case Nothing:
			break;
		}
	}
	return Nothing;
}