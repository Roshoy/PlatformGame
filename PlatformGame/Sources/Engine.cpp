#include "Engine.h"
#include "Player.h"
#include "Fruk.h"

std::string Engine::texturesDir = "Textures/";

Engine::Engine(sf::RenderWindow& win) {
	window = &win;
	map_view = sf::View(window->getDefaultView());
	map = Map();
	screenSpeed.x = 0;
	screenSpeed.y = 0;
	maxScreenSpeed.x = 10;
	maxScreenSpeed.y = 23;
	textureManager.loadTextures();	
}

Engine::GameState Engine::runEngine()
{		
	textureManager.setMapTextures(map);
	map.loadMapFile();
	spawnPlayer();
	spawnEnemy();		
	
	collisionManager = CollisionManager(player, enemies, map);

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
		
		window->setView(map_view);
		window->clear();
		window->draw(map);
		window->draw(player);
		
		for (const auto& enemy: enemies) {
			window->draw(enemy);
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
	if (MPlayerPos.x + player.getSize().x > window->getSize().x - 250 && map_view.getCenter().x + window->getSize().x / 2 < 
		map.getMapRange().x * Field::fieldSize - screenSpeed.x - 1) {
		if (maxScreenSpeed.x > screenSpeed.x + player.getMaxAcceleration().x) {
			screenSpeed.x += player.getMaxAcceleration().x;
		}
		else {
			screenSpeed.x = maxScreenSpeed.x;
		}
		map_view.move(screenSpeed.x, 0);
	}
	else if (MPlayerPos.x < 250 && map_view.getCenter().x - window->getSize().x / 2 > 0 + screenSpeed.x + 1) {
		if (maxScreenSpeed.x > screenSpeed.x + player.getMaxAcceleration().x) {
			screenSpeed.x += player.getMaxAcceleration().x;
		}
		else {
			screenSpeed.x = maxScreenSpeed.x;
		}
		map_view.move(-screenSpeed.x, 0);
	}
	else {
		screenSpeed.x= 0;
	}

	if (MPlayerPos.y > window->getSize().y - 250 && map_view.getCenter().y + window->getSize().y / 2 <
		map.getMapRange().y * Field::fieldSize - screenSpeed.y - 1) {
		if (maxScreenSpeed.y > screenSpeed.y) {
			screenSpeed.y += player.getMaxAcceleration().y;
		}
		map_view.move(0, screenSpeed.y);
	}
	else if (MPlayerPos.y < 100 &&
		map_view.getCenter().y - window->getSize().y / 2 > 0 + screenSpeed.y + 1) {
		if (maxScreenSpeed.y > screenSpeed.y) {
			screenSpeed.y += player.getMaxAcceleration().y;
		}
		map_view.move(0, -screenSpeed.y);
	}
	else {
		screenSpeed.y = 0;
	}
}

sf::Vector2i Engine::getPlayerInput() 
{
	auto direction = sf::Vector2i(0,0);
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		direction.x = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		direction.x = 1;
	}	
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		direction.y = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		map.saveMapFile();
	}
	return direction;
}

Engine::GameState Engine::playerMovement()
{	
	player.updateSpeed(getPlayerInput());
	player.updateNextPosition(
		collisionManager.characterCollisionWithMap(
			player.getCurrentRect(), player.getNextRect()));
	CollisionManager::CollisionResult res = collisionManager.playerCollisionWithEnemies();
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
	for (auto& enemy : enemies) {
		sf::Vector2i direction;
		if (enemy.getSpeed().x <= 0) {
			direction.x = -1;
		}
		else if (enemy.getSpeed().x > 0) {
			direction.x = 1;
		}
		
		enemy.updateSpeed(direction);
		sf::Vector2f newPosition = collisionManager.characterCollisionWithMap(enemy.getCurrentRect(), enemy.getNextRect());
		enemy.updateNextPosition(newPosition);
		enemy.updatePosition();
	}
}

void Engine::spawnPlayer()
{
	player = Player();
	player.setTextures(textureManager.getPlayerTextures());

	player.spawn(map.GetSpawnPoints(Character::CharacterType::Player)[0].x, map.GetSpawnPoints(Character::CharacterType::Player)[0].y);
	maxScreenSpeed.x = player.getMaxSpeed().x;
	maxScreenSpeed.y = player.getMaxSpeed().y;
}

void Engine::spawnEnemy()
{
	enemies.clear();
	for(const auto& spawnPoint : map.GetSpawnPoints(Character::CharacterType::Fruk))
	{
		Character* newEnemy = new Fruk();
		newEnemy->setTextures(textureManager.getFrukTextures());
		enemies.push_back(*newEnemy);
		enemies.back().spawn(spawnPoint.x, spawnPoint.y);
	}
}

Engine::GameState Engine::activateFieldsUnderCharacter(Character& character)
{
	sf::Rect<float> characterRect = character.getCurrentRect();
	for(int x = characterRect.left/Field::fieldSize; x<characterRect.width/Field::fieldSize; x++)
	{
		for (int y = characterRect.top / Field::fieldSize; y < characterRect.height / Field::fieldSize; y++)
		{		
			
		
		}
	}
	return GameState::On;
}

bool Engine::playerWon()
{
	return characterOnTile(player, 10, 0);
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
