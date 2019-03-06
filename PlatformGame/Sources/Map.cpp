#include "Map.h"
#include "Fields/SpawnPoint.h"

sf::Vector2i Map::mapDimensions;

Map::Map(int x, int y)
{	
	background = new RectangleShape(Vector2f(0, 0));
	background->setFillColor(Color(100, 150, 255));	

	fieldTypesMap[Field::Empty] = &createInstance<Field>;
	
	setMapSize(x, y);
}

void Map::setField(int x, int y, int type)
{
	if (x < 0 || y < 0 || x >= mapDimensions.x || y >= mapDimensions.y) {
		return;
	}
	
	fields[x][y] = new Field(x,y);
	fields[x][y]->setSolid(isSolidTexture(type));
	fields[x][y]->typeT=type;
	fields[x][y]->setTexture(texture[type]);
}

void Map::setMapSize(int x, int y)
{
	fields = new Field**[x];
	for(int i =0; i<x; i++)
	{
		fields[i] = new Field*[y];
		for(int j = 0; j<y; j++)
		{
			fields[i][j] = nullptr;
		}
	}
	
	mapDimensions = sf::Vector2i(x,y);
	
		
	background->setSize(Vector2f(x*Field::fieldSize, y*Field::fieldSize));
}

void Map::saveMapFile()
{
	fstream file;
	file.open("MapFile1.txt", ios::out | ios::trunc);
	if (!file.good()) {
		cout << "Blad zapisu mapy" << endl;
	}
	

	if (mapDimensions.x > 0) {
		for (int y = 0; y < mapDimensions.y; y++) {
			for (int x = 0; x < mapDimensions.x; x++) {
				file << fields[x][y]->getType() << " ";
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
				
				int t;
				file >> t;
				cout << t << " ";
				setField(x, y, t);
			}
			cout << endl;
		}
	}
}

void Map::setTextures(sf::Texture * texture)
{
	this->texture = texture;
}

Field Map::getField(Vector2f position)
{
	int x = position.x / Field::fieldSize;
	int y = position.y / Field::fieldSize;
	if (x < mapDimensions.x && y < mapDimensions.y) {
		return *fields[x][y];
	}
	return NULL;
}

Field Map::getField(int x, int y)
{
	if (x >= 0 && y >= 0 &&
		x < mapDimensions.x && y < mapDimensions.y) {
		return *fields[x][y];
	}
	return NULL;
}

Vector2i Map::getMapRange()
{
	return Vector2i(mapDimensions.x, mapDimensions.y);
}

bool Map::isSolidTexture(int ind)
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
	target.draw(*background, transform);
	for (int x = 0; x < mapDimensions.x; x++) {
		for (int y = 0; y < mapDimensions.y; y++) {
			
			if (fields[x][y] != nullptr) {
				target.draw(*fields[x][y], transform);
			}
		}
	}
}
