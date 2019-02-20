#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Character.h"
#include <list>

using namespace sf;
using namespace std;

class Engine {
public:
	enum GameState { On, Win, Lose };
	Engine(RenderWindow& win);
	GameState runEngine();
	void scrollMap();
	void getControlsInputToPlayer() const;
	GameState playerMovement();
	void frukMovement();

	static bool collisionWillBeBetweenCharacters(Character& objA, Character& objB);
	enum CollisionResult{Nothing, ADies, BDies};
	CollisionResult collisionOutcome(Character& objA, Character& objB);

	GameState playerCollisionWithEnemies();

	GameState collisionY(vector<Character>& enemy);

	GameState collisionX(vector<Character>& enemy);

private:
	void spawnPlayer();
	void spawnEnemy();
	float screenSpeedX;
	float screenSpeedY;
	float maxScreenSpeed;
	Map* map;
	RenderWindow* window;
	Character* player;
	std::list<Character> enemies;
	View* map_view;
	static std::string texturesDir;
	int tileCounting(int type);
	bool playerWon();
	bool characterOnTileType(Character& character, int tileType);

};