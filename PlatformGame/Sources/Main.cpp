#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "Game.h"

int main()
{
	
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000.f, 1000.f), "Platform");
	window->setFramerateLimit(60);

	Game* game = new Game(*window);
	game->runGame();
	/*int g;
	cin >> g;*/
	return 0;
}