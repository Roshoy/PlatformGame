#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Character.h"
#include <list>


class CollisionManager
{
public:
	CollisionManager() = default;
	CollisionManager(Player& player, std::list<Character*>& enemies, Map& map);
	
	enum CollisionResult { Nothing, ADies, BDies };

	CollisionResult playerCollisionWithEnemies();

	sf::Vector2f characterCollisionWithMap(Rect<float> currentRect, Rect<float> lastRect);	

private:
	bool groundUnderneath(sf::Rect<float> currentRect);
	static bool collisionWillBeBetweenCharacters(Character& objA, Character& objB);
	CollisionResult collisionBetweenCharactersOutcome(Character& objA, Character& objB);
	bool rectCollisionWithMap(Rect<float> currentRect);
	sf::Vector2f approximatePositionX(Rect<float> currentRect);
	sf::Vector2f approximatePositionY(Rect<float> currentRect);
	Player* player;
	std::list<Character*>* enemies;
	Map* map;
	float getUpMoveLimit(FloatRect character, float dy);
	float getRightMoveLimit(FloatRect character, float dx);
	float getDownMoveLimit(FloatRect character, float dy);
	float getLeftMoveLimit(FloatRect character, float dx);

};

