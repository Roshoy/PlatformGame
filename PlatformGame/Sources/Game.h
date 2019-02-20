#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "Button.h"
#include "Menu.h"


using namespace std;

class Game {
public:
	Game(sf::RenderWindow& win);
	bool runGame();
	Engine* engine;
	Menu* mainMenu;
	Menu* winMenu;
	Menu* loseMenu;

	
private:
	Engine::GameState gameState;
	sf::Font* font;
	sf::RenderWindow* window;
};