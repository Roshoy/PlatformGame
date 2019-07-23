#include "Map.h"
#include "Fields/Field.h"

sf::Vector2i Map::mapDimensions;

Map::Map(int x, int y)
{	
	background = RectangleShape(sf::Vector2f(0, 0));
	background.setFillColor(sf::Color(100, 150, 255));	
	//background->setFillColor(sf::Color::Black);
	sf::Vector2i playerSpwnPoint(0,0);
	sf::Vector2i enemySpwnPoint(50, 0);

	/////// Fast ugly workaround just to make it work
	std::vector<sf::Vector2i> psps;
	psps.push_back(playerSpwnPoint);
	std::vector<sf::Vector2i> esps;
	esps.push_back(enemySpwnPoint);
	spawnPoints.insert(std::pair<Character::CharacterType, std::vector<sf::Vector2i>>
		(Character::CharacterType::Player, psps));
	spawnPoints.insert(std::pair<Character::CharacterType, std::vector<sf::Vector2i>>
		(Character::CharacterType::Fruk, esps));
	////////////////////////////////
	setMapSize(x, y);
}

void Map::setField(int x, int y, int textureId)
{
	if (x < 0 || y < 0 || x >= mapDimensions.x || y >= mapDimensions.y) {
		return;
	}
	
	fields[x][y] = Field(x,y);
	fields[x][y].setSolid(isSolidTexture(textureId));
	//fields[x][y]->typeT=type;
	fields[x][y].setTexture(textures[textureId]);
}

void Map::setMapSize(int x, int y)
{
	fields = new Field*[x];
	for(int i =0; i<x; i++)
	{
		fields[i] = new Field[y];
	}
	
	mapDimensions = sf::Vector2i(x,y);
	
	background.setSize(Vector2f(x*Field::fieldSize, y*Field::fieldSize));
}

void Map::saveMapFile() const
{
	fstream file;
	file.open("MapFile1.txt", ios::out | ios::trunc);
	if (!file.good()) {
		cout << "Blad zapisu mapy" << endl;
	}
	

	if (mapDimensions.x > 0) {
		for (int y = 0; y < mapDimensions.y; y++) {
			for (int x = 0; x < mapDimensions.x; x++) {
				file << fields[x][y].getType() << " ";
			}
			if (y != mapDimensions.y - 1) {
				file << "\n";
			}
		}
	}
}

void Map::loadMapFile()
{
	fstream file;
	file.open("MapFile.txt", ios::in);
	if (!file.good()) {
		std::cout << "Blad wczytania mapy" << std::endl;
	}
	int x;
	int y;
	
	file >> x;
	file >> y;

	setMapSize(x, y);

	if (x > 0 && y > 0) {
		for (y = 0; y < mapDimensions.y; y++) {
			for (x = 0; x < mapDimensions.x; x++) {
				int textureId;
				file >> textureId;
				setField(x, y, textureId);
			}
		}
	}
}

void Map::setTextures(const std::vector<sf::Texture>& texture)
{
	this->textures = texture;
}

Field Map::getField(const sf::Vector2f& position) const
{
	int x = position.x / Field::fieldSize;
	int y = position.y / Field::fieldSize;
	if (x < mapDimensions.x && y < mapDimensions.y) {
		return fields[x][y];
	}
	return NULL;
}

Field Map::getField(int x, int y) const
{
	if (x >= 0 && y >= 0 &&
		x < mapDimensions.x && y < mapDimensions.y) {
		return fields[x][y];
	}
	return NULL;
}

Vector2i Map::getMapRange() const
{
	return Vector2i(mapDimensions.x, mapDimensions.y);
}

std::vector<sf::Vector2i> Map::GetSpawnPoints(const Character::CharacterType & type) const
{
	return spawnPoints.at(type);
}

bool Map::isSolidTexture(int ind) const
{
	int notSolidInd[] = {8,9,16,17,18,19,24,25,35,36,37,38,39,45,46,48,49,55,56,57,58,59};
	
	for (int i : notSolidInd)
	{
		if (ind == i) {			
			return false;
		}
	}
	return true;
}

void Map::draw(RenderTarget & target, RenderStates states) const
{
	Transform transform = getTransform();
	target.draw(background, transform);
	for (int x = 0; x < mapDimensions.x; x++) {
		for (int y = 0; y < mapDimensions.y; y++) {
			target.draw(fields[x][y], transform);
		}
	}
}
