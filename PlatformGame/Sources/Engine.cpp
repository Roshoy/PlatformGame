#include "Engine.h"
#include "Player.h"
#include "Fruk.h"

std::string Engine::texturesDir = "Textures/";

Engine::Engine(sf::RenderWindow& win) {
	window = &win;
	map_view = new sf::View(window->getDefaultView());
	map = new Map();
	screenSpeed.x = 0;
	screenSpeed.y = 0;
	maxScreenSpeed.x = 10;
	maxScreenSpeed.y = 23;
	textureManager.loadTextures();	
}

Engine::GameState Engine::runEngine()
{		
	textureManager.setMapTextures(*map);
	map->loadMapFile();
	spawnPlayer();
	spawnEnemy();	
	
	
	collisionManager = new CollisionManager(player, enemies, *map);

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
		window->draw(player);
		
		for (std::list<Character*>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
			window->draw(**i);
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
	if (MPlayerPos.x + player.getSize().x > window->getSize().x - 250 && map_view->getCenter().x + window->getSize().x / 2 < 
		map->getMapRange().x * Field::fieldSize - screenSpeed.x - 1) {
		if (maxScreenSpeed.x > screenSpeed.x + player.getMaxAcceleration().x) {
			screenSpeed.x += player.getMaxAcceleration().x;
		}
		else {
			screenSpeed.x = maxScreenSpeed.x;
		}
		map_view->move(screenSpeed.x, 0);
	}
	else if (MPlayerPos.x < 250 && map_view->getCenter().x - window->getSize().x / 2 > 0 + screenSpeed.x + 1) {
		if (maxScreenSpeed.x > screenSpeed.x + player.getMaxAcceleration().x) {
			screenSpeed.x += player.getMaxAcceleration().x;
		}
		else {
			screenSpeed.x = maxScreenSpeed.x;
		}
		map_view->move(-screenSpeed.x, 0);
	}
	else {
		screenSpeed.x= 0;
	}

	if (MPlayerPos.y > window->getSize().y - 250 && map_view->getCenter().y + window->getSize().y / 2 <
		map->getMapRange().y * Field::fieldSize - screenSpeed.y - 1) {
		if (maxScreenSpeed.y > screenSpeed.y) {
			screenSpeed.y += player.getMaxAcceleration().y;
		}
		map_view->move(0, screenSpeed.y);
	}
	else if (MPlayerPos.y < 100 &&
		map_view->getCenter().y - window->getSize().y / 2 > 0 + screenSpeed.y + 1) {
		if (maxScreenSpeed.y > screenSpeed.y) {
			screenSpeed.y += player.getMaxAcceleration().y;
		}
		map_view->move(0, -screenSpeed.y);
	}
	else {
		screenSpeed.y = 0;
	}
}

sf::Vector2i Engine::getPlayerInput() 
{
	sf::Vector2i* direction = new sf::Vector2i(0,0);
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		direction->x = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		direction->x = 1;
	}	
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		direction->y = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		map->saveMapFile();
	}
	return *direction;
}

Engine::GameState Engine::playerMovement()
{	
	player.updateSpeed(getPlayerInput());
	player.updateNextPosition(
		collisionManager->characterCollisionWithMap(
			player.getCurrentRect(), player.getNextRect()));
	CollisionManager::CollisionResult res = collisionManager->playerCollisionWithEnemies();
	GameState gameState = On;
	if (res == CollisionManager::ADies)gameState = Lose;
	player.updatePosition();
	if (gameState != On) {
		return gameState;
	}
	//cout << "Player pos: " << player.getCurrentRect().left << " " << player.getCurrentRect().top << endl;
	if (playerWon()) {
		return Win;
	}
	return On;
}

void Engine::frukMovement()
{
	for (std::list<Character*>::iterator iter = enemies.begin(); iter != enemies.end(); ++iter) {
		sf::Vector2i direction;
		if ((*iter)->getSpeed().x < 0) {
			direction.x = -1;
		}
		else if ((*iter)->getSpeed().x > 0) {
			direction.x = 1;
		}
		
		(*iter)->updateSpeed(direction);
		sf::Vector2f newPosition = collisionManager->characterCollisionWithMap((*iter)->getCurrentRect(), (*iter)->getNextRect());
		(*iter)->updateNextPosition(newPosition);
		(*iter)->updatePosition();
	}
}

void Engine::spawnPlayer()
{
	player = Player();
	player.setTextures(*textureManager.getPlayerTextures());

	player.spawn(mapScripts.playerSpawnPoint.first, mapScripts.playerSpawnPoint.second);
	maxScreenSpeed.x = player.getMaxSpeed().x;
	maxScreenSpeed.y = player.getMaxSpeed().y;
}

void Engine::spawnEnemy()
{
	enemies.clear();
	for(auto it = mapScripts.frukSpawnPoints.begin();it != mapScripts.frukSpawnPoints.end(); ++it)
	{
		Character* newEnemy = new Fruk();
		newEnemy->setTextures(*textureManager.getFrukTextures());
		enemies.push_back(newEnemy);
		enemies.back()->spawn(it->first, it->second);
	}
}

bool Engine::playerWon()
{
	for(auto it = mapScripts.winningPoints.begin(); it != mapScripts.winningPoints.end(); ++it)
	{
		if (characterOnTile(player, it->first, it->second))
		{
			return true;
		}
	}
	return false;
}

bool Engine::characterOnTile(Character & character, int x, int y)
{
	sf::Rect<float> currentRect = character.getCurrentRect();
	for (int xi = currentRect.left / Field::fieldSize; xi <= (currentRect.left + currentRect.width) / Field::fieldSize; xi++)
	{
		for (int yi = currentRect.top / Field::fieldSize; yi <= (currentRect.top + currentRect.height) / Field::fieldSize; yi++)
		{
			if (xi == x && yi == y)
			{
				return true;
			}
		}
	}
	return false;
}
