#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <list>
#include "Map.h"


class CollisionManager
{
public:
	CollisionManager() = default;
	CollisionManager(const Player& player, const std::list<Character>& enemies, const Map& map):
		player(player), enemies(enemies), map(map){}
	
	enum CollisionResult { Nothing, ADies, BDies };

	CollisionResult playerCollisionWithEnemies();

	sf::Vector2f characterCollisionWithMap(const sf::Rect<float>& currentRect, const sf::Rect<float>& lastRect);	

private:
	bool groundUnderneath(const sf::Rect<float> currentRect);
	static bool collisionWillBeBetweenCharacters(const Character& objA, const Character& objB);
	CollisionResult collisionBetweenCharactersOutcome(const Character& objA, const Character& objB);
	bool rectCollisionWithMap(const sf::Rect<float>& currentRect);
	sf::Vector2f approximatePositionX(const sf::Rect<float>& currentRect);
	sf::Vector2f approximatePositionY(const sf::Rect<float>& currentRect);
	Player player;
	std::list<Character> enemies;
	Map map;
	float getUpMoveLimit(const sf::FloatRect& character, float dy) const;
	float getRightMoveLimit(const sf::FloatRect& character, float dx) const;
	float getDownMoveLimit(const sf::FloatRect& character, float dy) const;
	float getLeftMoveLimit(const sf::FloatRect& character, float dx) const;

};

