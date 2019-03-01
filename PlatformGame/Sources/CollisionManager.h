#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Character.h"
#include <list>


class CollisionManager
{
public:
	CollisionManager();
	CollisionManager(Player& player, std::list<Character>& enemies);
	~CollisionManager();
	void setTestString(std::string* str);
	static bool collisionWillBeBetweenCharacters(Character& objA, Character& objB);
	enum CollisionResult { Nothing, ADies, BDies };
	CollisionResult collisionOutcome(Character& objA, Character& objB);

	CollisionResult playerCollisionWithEnemies();
private:
	Player* player;
	std::list<Character>* enemies;
	std::string *testString;
};

