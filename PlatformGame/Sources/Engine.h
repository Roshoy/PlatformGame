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

enum class GameState { On, Win, Lose };

class Engine {
public:
	Engine(RenderWindow& win);
	GameState runEngine();
	void scrollMap();
	sf::Vector2i getPlayerInput();
	GameState playerMovement();
	void frukMovement();


private:
	CollisionManager _collisionManager;
	TextureManager _textureManager;
	void spawnPlayer();
	void spawnEnemy();
	sf::Vector2f _screenSpeed;
	sf::Vector2f _maxScreenSpeed;
	Map _map;
	RenderWindow* _window;
	Player _player;
	std::list<Character*> _enemies;
	View _map_view;
	static std::string _texturesDir;

	GameState activateFieldsUnderCharacter(Character& character);
	bool playerWon();
	bool characterOnTile(Character& character, int x, int y);

};