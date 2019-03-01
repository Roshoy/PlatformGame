#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Character.h"
#include <list>
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Engine {
public:
	enum GameState { On, Win, Lose };
	Engine(RenderWindow& win);
	GameState runEngine();
	void scrollMap();
	void getControlsInputToPlayer();
	GameState playerMovement();
	void frukMovement();


private:
	std::string testString;
	CollisionManager* collisionManager;
	TextureManager textureManager;
	void spawnPlayer();
	void spawnEnemy();
	float screenSpeedX;
	float screenSpeedY;
	float maxScreenSpeed;
	Map* map;
	RenderWindow* window;
	Player player;
	std::list<Character> enemies;
	View* map_view;
	static std::string texturesDir;

	bool playerWon();
	bool characterOnTileType(Character& character, int tileType);

};