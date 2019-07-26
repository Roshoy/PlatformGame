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
	sf::Vector2i getPlayerInput();
	GameState playerMovement();
	void frukMovement();


private:
	CollisionManager collisionManager;
	TextureManager textureManager;
	void spawnPlayer();
	void spawnEnemy();
	sf::Vector2f screenSpeed;
	sf::Vector2f maxScreenSpeed;
	Map map;
	RenderWindow* window;
	Player player;
	std::list<Character*> enemies;
	View map_view;
	static std::string texturesDir;

	Engine::GameState activateFieldsUnderCharacter(Character& character);
	bool playerWon();
	bool characterOnTile(Character& character, int x, int y);

};