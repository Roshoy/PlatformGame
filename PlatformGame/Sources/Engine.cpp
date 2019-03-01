#include "Engine.h"
#include "Player.h"
#include "Fruk.h"

std::string Engine::texturesDir = "Textures/";

Engine::Engine(sf::RenderWindow& win) {
	window = &win;
	map_view = new sf::View;
	map = new Map();
	screenSpeedX = 0;
	screenSpeedY = 0;
	maxScreenSpeed = 10;
	textureManager.loadTextures();
	testString = "Start";
}

Engine::GameState Engine::runEngine()
{		
	textureManager.setMapTextures(*map);
	map->loadMapFile();
	
	spawnPlayer();
	spawnEnemy();	
	collisionManager = new CollisionManager(player, enemies);
	collisionManager->setTestString(&testString);
	GameState gameState = On;

	while (window->isOpen()) {
		//testString = player.getPosition().x;
		//std::cout << testString << '\n';
		Event event;
		if (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}
		}
		
		frukMovement();
		
		gameState = playerMovement();
		
		scrollMap();
		
		window->setView(*map_view);
		window->clear();
		window->draw(*map);
		window->draw(player);
		
		for (std::list<Character>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
			window->draw(*i);
		}
		window->display();
		if (gameState != On) {
			return gameState;
		}
		
	}
	return On;
}


void Engine::scrollMap()
{
	Vector2i MPlayerPos = window->mapCoordsToPixel(player.getPosition());

	if (MPlayerPos.x + player.getSize().x > 700 && map_view->getCenter().x + window->getSize().x / 2 < 
		map->getMapRange().x * map->scale - screenSpeedX - 1) {
		if (maxScreenSpeed > screenSpeedX) {
			screenSpeedX += 1.f;
		}

		map_view->move(screenSpeedX, 0);
	}
	else if (MPlayerPos.x < 300 && map_view->getCenter().x - window->getSize().x / 2 > 0 + screenSpeedX + 1) {
		if (maxScreenSpeed > screenSpeedX) {
			screenSpeedX += 1.f;
		}
		map_view->move(-screenSpeedX, 0);
	}
	else {
		screenSpeedX = 0;
	}

	if (MPlayerPos.y > 800 && map_view->getCenter().y + window->getSize().y / 2 < map->getMapRange().y * map->scale - screenSpeedY - 1) {
		if (maxScreenSpeed > screenSpeedY) {
			screenSpeedY += 1.f;
		}

		map_view->move(0, screenSpeedY);
	}
	else if (MPlayerPos.y < 200 && map_view->getCenter().y - window->getSize().y / 2 > 0 + screenSpeedY + 1) {
		if (maxScreenSpeed > screenSpeedY) {
			screenSpeedY += 1.f;
		}
		map_view->move(0, -screenSpeedY);
	}
	else {
		screenSpeedY = 0;
	}
}

void Engine::getControlsInputToPlayer() 
{
	sf::Vector2i* direction = new sf::Vector2i(0,0);
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		direction->x = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		direction->x = 1;
	}	
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		direction->y = 1;
	}
	player.updateSpeed(*direction);
}

Engine::GameState Engine::playerMovement()
{	
	getControlsInputToPlayer();
	player.updateNextPosition(*map);
	CollisionManager::CollisionResult res = collisionManager->playerCollisionWithEnemies();
	GameState gameState = On;
	if (res == CollisionManager::ADies)gameState = Lose;
	player.updatePosition();
	if (gameState != On) {
		return gameState;
	}
	
	if (playerWon()) {
		return Win;
	}
	return On;
}

void Engine::frukMovement()
{
	for (std::list<Character>::iterator iter = enemies.begin(); iter != enemies.end(); ++iter) {
		sf::Vector2i direction;
		if (iter->getSpeed().x < 0) {
			direction.x = -1;
		}
		else if (iter->getSpeed().x > 0) {
			direction.x = 1;
		}
		else {
			FloatRect enemyRect = iter->getCurrentRect();

			if (enemyRect.left == map->getLeftMoveLimit(enemyRect) && enemyRect.left + enemyRect.width < map->getRightMoveLimit(enemyRect)) {
				direction.x = 1;
			}
			else if ( enemyRect.left != map->getLeftMoveLimit(enemyRect)) {
				direction.x = -1;
			}			
		}

		iter->updateSpeed(direction);
		iter->updateNextPosition(*map);		
		iter->updatePosition();
	}
}


void Engine::spawnPlayer()
{
	int x = 0, y = 0;
	player = Player();
	if (!player.spawn(*map, 2, x, y))
	{
		std::cout << "No Player spawned!\n";
	};
	
	textureManager.setCharacterTextures(player);
}

void Engine::spawnEnemy()
{
	enemies.clear();
	int x = 0, y = 0;
	do {
		Character* newEnemy = new Fruk();
		textureManager.setCharacterTextures(*newEnemy);
		enemies.push_back(*newEnemy);
	} while (enemies.back().spawn(*map, 3, x, y));
	enemies.pop_back();
}

bool Engine::playerWon()
{
	return characterOnTileType(player, 4);
}

bool Engine::characterOnTileType(Character & character, int tileType)
{
	sf::Vector2f characterPos = character.getPosition();
	sf::FloatRect characterRect = character.getCurrentRect();
	if (map->getFieldType(characterPos) == tileType) {
		return true;
	}
	if (map->getFieldType(characterPos + Vector2f(characterRect.width, 0)) == tileType) {
		return true;
	}
	if (map->getFieldType(characterPos + Vector2f(0, characterRect.height)) == tileType) {
		return true;
	}
	if (map->getFieldType(characterPos + Vector2f(-characterRect.width, 0)) == tileType) {//???
		return true;
	}
	return false;
}
