#include "Game.h"

Game::Game(sf::RenderWindow & win)
{
	window = &win;
	engine = new Engine(*window);
	font = new sf::Font;
	font->loadFromFile("Fonts/Semi-Coder-Regular.otf");
	mainMenu = new Menu(*window, *font);
	winMenu = new Menu(*window, *font);
	loseMenu = new Menu(*window, *font);

	mainMenu->addButton("Start");
	mainMenu->addButton("Exit");
	
	winMenu->addButton("Try again");
	winMenu->addButton("Main menu");
	winMenu->addButton("Exit");

	loseMenu->addButton("Try again");
	loseMenu->addButton("Main menu");
	loseMenu->addButton("Exit");

	mainMenu->setTitle("Main Menu");
	winMenu->setTitle("You Won!");
	loseMenu->setTitle("You Lose :(");

}

bool Game::runGame()
{
	gameState = Engine::On;
	cout << "Shiet!\n";
	while (true) {
		if (gameState == Engine::On) {
			switch (mainMenu->runMenu()) {
			case 0:
				gameState = engine->runEngine();
				break;
			case 1:
				return 0;
				break;
			}
		}

		if (gameState == Engine::Win) {
			cout << "Win!\n";
			switch (winMenu->runMenu()) {
			case 0:
				gameState = engine->runEngine();
				break;
			case 1:
				return runGame();
				break;
			case 2:
				return 0;
				break;
			}
		}

		if (gameState == Engine::Lose) {
			cout << "Lose!\n";
			switch (loseMenu->runMenu()) {
			case 0:
				gameState = engine->runEngine();
				break;
			case 1:
				cout << "2 przycisk\n";
				return runGame();
				break;
			case 2:
				return 0;
				break;
			}
		}
	}


	
}
