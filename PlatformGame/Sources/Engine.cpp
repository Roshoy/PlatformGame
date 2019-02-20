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
}

Engine::GameState Engine::runEngine()
{	
	
	map->loadMapFile();
	spawnPlayer();
	spawnEnemy();
	

	GameState gameState = On;

	while (window->isOpen()) {
		
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
		window->draw(*player);
		
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
	Vector2i MPlayerPos = window->mapCoordsToPixel(player->getPosition());

	if (MPlayerPos.x + player->getSize().x > 700 && map_view->getCenter().x + window->getSize().x / 2 < 
		map->getMapRange().x * map->size - screenSpeedX - 1) {
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

	if (MPlayerPos.y > 800 && map_view->getCenter().y + window->getSize().y / 2 < map->getMapRange().y * map->size - screenSpeedY - 1) {
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

void Engine::getControlsInputToPlayer() const
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
	player->updateSpeed(*direction);
}

Engine::GameState Engine::playerMovement()
{	
	getControlsInputToPlayer();
	player->updateNextPosition(*map);

	GameState gameState = playerCollisionWithEnemies();
	player->updatePosition();
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

bool Engine::collisionWillBeBetweenCharacters(Character & objA, Character & objB)
{
	sf::FloatRect objARect = objA.getNextRect();
	sf::FloatRect objBRect = objB.getNextRect();

	return objARect.intersects(objBRect);
}

Engine::CollisionResult Engine::collisionOutcome(Character & objA, Character & objB)
{
	if(!collisionWillBeBetweenCharacters(objA,objB))
	{
		return Nothing;
	}
	if(objA.getCharacterType() == "Player" &&
		objA.getCurrentRect().height + objA.getCurrentRect().top < objB.getCurrentRect().top)
	{
		return BDies;
	}
	if(objA.getCharacterType() == "Player")
	{
		return ADies;
	}	
	return Nothing;
}

Engine::GameState Engine::playerCollisionWithEnemies()
{
	for (std::list<Character>::iterator iter = enemies.begin(); iter != enemies.end(); ++iter)
	{
		
		switch (collisionOutcome(*player, *iter))
		{
		case ADies:
			return Lose;
		case BDies:
			enemies.erase(iter++);
			iter--;
			break;
		case Nothing:
			break;
		}
	}
	return On;
}

void Engine::spawnPlayer()
{
	int x = 0, y = 0;
	player = new Player();
	if (!player->spawn(*map, 2, x, y))
	{
		std::cout << "No Player spawned!\n";
	};

	player->loadTexture(texturesDir);
}

void Engine::spawnEnemy()
{
	enemies.clear();
	int x = 0, y = 0;
	do {
		Character* newEnemy = new Fruk();
		newEnemy->loadTexture(texturesDir);
		enemies.push_back(*newEnemy);
	} while (enemies.back().spawn(*map, 3, x, y));
	enemies.pop_back();
}

int Engine::tileCounting(int type)
{
	int w = 0;
	for (int x = 0; x < map->getMapRange().x; x++) {
		for (int y = 0; y < map->getMapRange().y; y++) {

			if (map->getFieldType(x, y) == type) {
				w++;
			}
		}
	}
	return w;
}

bool Engine::playerWon()
{
	return characterOnTileType(*player, 4);
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
