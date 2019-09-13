#include "Engine.h"
#include "Player.h"
#include "Fruk.h"

std::string Engine::_texturesDir = "Textures/";

Engine::Engine(sf::RenderWindow& win) {
	_window = &win;
	_map_view = sf::View(_window->getDefaultView());
	_map = Map();
	_screenSpeed.x = 0;
	_screenSpeed.y = 0;
	_maxScreenSpeed.x = 10;
	_maxScreenSpeed.y = 23;
	_textureManager.loadTextures();	
}

GameState Engine::runEngine()
{		
	_textureManager.setMapTextures(_map);
	_map.loadMapFile();
	spawnPlayer();
	spawnEnemy();		
	
	_collisionManager.Init(_player, _enemies, _map);

	GameState gameState = GameState::On;
	cout << endl<<Map::_mapDimensions.x << endl;
	while (_window->isOpen()) {
		Event event;
		if (_window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				_window->close();
			}
		}
		
		frukMovement();
		
		gameState = playerMovement();
		
		scrollMap();
		
		_window->setView(_map_view);
		_window->clear();
		_window->draw(_map);
		_window->draw(_player);
		
		for (const auto& enemy: _enemies) {
			_window->draw(*enemy);
		}
		_window->display();
		if (gameState != GameState::On) {
			return gameState;
		}
		
	}
	return GameState::On;
}


void Engine::scrollMap()
{
	Vector2i MPlayerPos = _window->mapCoordsToPixel(_player.getPosition());
	if (MPlayerPos.x + _player.getSize().x > _window->getSize().x - 250 && _map_view.getCenter().x + _window->getSize().x / 2 < 
		_map.getMapRange().x * Field::_fieldSize - _screenSpeed.x - 1) {
		if (_maxScreenSpeed.x > _screenSpeed.x + _player.getMaxAcceleration().x) {
			_screenSpeed.x += _player.getMaxAcceleration().x;
		}
		else {
			_screenSpeed.x = _maxScreenSpeed.x;
		}
		_map_view.move(_screenSpeed.x, 0);
	}
	else if (MPlayerPos.x < 250 && _map_view.getCenter().x - _window->getSize().x / 2 > 0 + _screenSpeed.x + 1) {
		if (_maxScreenSpeed.x > _screenSpeed.x + _player.getMaxAcceleration().x) {
			_screenSpeed.x += _player.getMaxAcceleration().x;
		}
		else {
			_screenSpeed.x = _maxScreenSpeed.x;
		}
		_map_view.move(-_screenSpeed.x, 0);
	}
	else {
		_screenSpeed.x= 0;
	}

	if (MPlayerPos.y > _window->getSize().y - 250 && _map_view.getCenter().y + _window->getSize().y / 2 <
		_map.getMapRange().y * Field::_fieldSize - _screenSpeed.y - 1) {
		if (_maxScreenSpeed.y > _screenSpeed.y) {
			_screenSpeed.y += _player.getMaxAcceleration().y;
		}
		_map_view.move(0, _screenSpeed.y);
	}
	else if (MPlayerPos.y < 100 &&
		_map_view.getCenter().y - _window->getSize().y / 2 > 0 + _screenSpeed.y + 1) {
		if (_maxScreenSpeed.y > _screenSpeed.y) {
			_screenSpeed.y += _player.getMaxAcceleration().y;
		}
		_map_view.move(0, -_screenSpeed.y);
	}
	else {
		_screenSpeed.y = 0;
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
		_map.saveMapFile();
	}
	return direction;
}

GameState Engine::playerMovement()
{	
	_player.updateSpeed(getPlayerInput());
	_player.updateNextPosition(
		_collisionManager.characterCollisionWithMap(
			_player.getCurrentRect(), _player.getNextRect()));
	CollisionManager::CollisionResult res = _collisionManager.playerCollisionWithEnemies();
	GameState gameState = GameState::On;
	if (res == CollisionManager::ADies)gameState = GameState::Lose;
	_player.updatePosition();
	if (gameState != GameState::On) {
		return gameState;
	}

	if (playerWon()) {
		return GameState::Win;
	}
	return GameState::On;
}

void Engine::frukMovement()
{
	for (auto& enemy : _enemies) {
		sf::Vector2i direction;
		if (enemy->getSpeed().x < 0) {
			direction.x = -1;
		}
		else if (enemy->getSpeed().x > 0) {
			direction.x = 1;
		}
		
		enemy->updateSpeed(direction);
		sf::Vector2f newPosition = _collisionManager.characterCollisionWithMap(enemy->getCurrentRect(), enemy->getNextRect());
		enemy->updateNextPosition(newPosition);
		enemy->updatePosition();
	}
}

void Engine::spawnPlayer()
{
	_player = Player();
	_player.setTextures(_textureManager.getCharacterTextures(Character::CharacterType::Player));

	_player.spawn(_map.GetSpawnPoints(Character::CharacterType::Player)[0].x, _map.GetSpawnPoints(Character::CharacterType::Player)[0].y);
	_maxScreenSpeed.x = _player.getMaxSpeed().x;
	_maxScreenSpeed.y = _player.getMaxSpeed().y;
}

void Engine::spawnEnemy()
{
	_enemies.clear();
	for(const auto& spawnPoint : _map.GetSpawnPoints(Character::CharacterType::Fruk))
	{
		Character* newEnemy = new Fruk();
		newEnemy->setTextures(_textureManager.getCharacterTextures(Character::CharacterType::Fruk));
		_enemies.push_back(newEnemy);
		_enemies.back()->spawn(spawnPoint.x, spawnPoint.y);
	}
}

GameState Engine::activateFieldsUnderCharacter(Character& character)
{
	sf::Rect<float> characterRect = character.getCurrentRect();
	for(int x = characterRect.left/Field::_fieldSize; x<characterRect.width/Field::_fieldSize; x++)
	{
		for (int y = characterRect.top / Field::_fieldSize; y < characterRect.height / Field::_fieldSize; y++)
		{		
			
		
		}
	}
	return GameState::On;
}

bool Engine::playerWon()
{
	return characterOnTile(_player, 10, 0);
}

bool Engine::characterOnTile(Character & character, int x, int y)
{
	sf::Rect<float> currentRect = character.getCurrentRect();
	for (int xi = currentRect.left / Field::_fieldSize; xi <= (currentRect.left + currentRect.width) / Field::_fieldSize; xi++)
	{
		for (int yi = currentRect.top / Field::_fieldSize; yi <= (currentRect.top + currentRect.height) / Field::_fieldSize; yi++)
		{
			if (xi == x && yi == y)
			{
				return true;
			}
		}
	}
	return false;
}
