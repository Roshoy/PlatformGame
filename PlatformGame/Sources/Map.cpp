#include "Map.h"



int Map::fieldTypesCount = 4;
std::string Map::texturesDir = "Textures/Fields/FieldsSpriteSheet.png";

Map::Map(float ssize, int x, int y)
{
	background = new RectangleShape(Vector2f(0, 0));
	background->setFillColor(Color(100, 150, 255));
	mapDimensions.x = x;
	mapDimensions.y = y;
	scale = ssize;

	fieldTypesMap[Field::Empty] = &createInstance<Field>;
	fieldTypesMap[Field::Brick] = &createInstance<BrickWall>;
	fieldTypesMap[Field::PlayerSpawn] = &createInstance<PlayerSpawn>;
	fieldTypesMap[Field::FrukSpawn] = &createInstance<Field>;
	fieldTypesMap[Field::Win] = &createInstance<Field>;
	setMapSize(x, y);
}

void Map::setField(int x, int y, int type)
{
	std::cout << "Przed!\n";
	if (x < 0 || y < 0 || x >= mapDimensions.x || y >= mapDimensions.y || 
		(fields[pair<int, int>(x,y)]!=nullptr && fields[pair<int, int>(x, y)]->getType() == type)) {
		return;
	}
	std::cout << "Po!\n";
	fields[pair<int, int>(x, y)] = fieldTypesMap[static_cast<Field::FieldType>(type)]();
	fields[pair<int, int>(x, y)]->init(scale, x, y, static_cast<Field::FieldType>(type));

	//if type is unique empty current field of that type 
	if(fields[pair<int,int>(x,y)]->isUnique())
	{
		for(auto it = fields.begin(); it != fields.end();++it)
		{
			std::cout << "Pierwsze pole do wpisania!\n";
			if(it->first != pair<int,int>(x,y) && it->second->getType() == type)
			{
				it->second = new Field();
				it->second->init(scale, x, y);
				break;
			}
		}
	}

	fields[pair<int, int>(x, y)]->setTexture(texture);
}

void Map::setMapSize(int x, int y)
{
	for (auto it = fields.begin(); it != fields.end(); ++it)
	{
		delete[] fields[it->first];
	}
	
	mapDimensions.x = x;
	mapDimensions.y = y;
		
	background->setSize(Vector2f(x*scale, y*scale));

}

void Map::saveMapFile()
{
	fstream file;
	file.open("MapFile1.txt", ios::out | ios::trunc);
	if (!file.good()) {
		cout << "Blad zapisu mapy" << endl;
	}
	file << scale << " " << mapDimensions.x << " " << mapDimensions.y << "\n";
	for (int i = 1; i < fieldTypesCount; i++) {
		file << "<" << i << "> ";
		for (auto it = fields.begin(); it != fields.end(); it++) {
			if ((int)it->second->getType() == i) {
				file << it->first.first << " " << it->first.second<<" ";
			}
		}
	}
	std::cout << "Map saved!\n";

/*
	if (mapDimensions.x > 0) {
		for (int y = 0; y < mapDimensions.y; y++) {
			for (int x = 0; x < mapDimensions.x; x++) {
				file << fields[pair<int, int>(x,y)]->getType() << " ";
			}
			if (y != mapDimensions.y - 1) {
				file << "\n";
			}
		}
	}*/
}

void Map::loadMapFile()
{
	fstream file;
	file.open("MapFile1.txt", ios::in);
	if (!file.good()) {
		std::cout << "Blad wczytania mapy" << std::endl;
	}
	int x;
	int y;
	file >> scale;
	file >> x;
	file >> y;

	setMapSize(x, y);

	Field::FieldType type = Field::Empty;
	std::string s;
	bool isXCoord = true;

	while (!file.eof()) {
		file >> s;
		if (s.length() > 0 && s[0] == '<' && s[s.length() - 1] == '>') {
			type = static_cast<Field::FieldType>(std::stoi(s.substr(1, s.length() - 2)));
		}
		else {
			if (isXCoord) {
				file >> x;
			}
			else {
				file >> y;
				setField(x, y, type);
			}
			isXCoord = !isXCoord;
		}

	}
	std::cout << "Map loaded!\n";

	//if (x > 0 && y > 0) {
	//	for (y = 0; y < mapDimensions.y; y++) {
	//		for (x = 0; x < mapDimensions.x; x++) {
	//			int t;
	//			file >> t;
	//			setField(x, y, t);
	//		}
	//	}
	//}

}

int Map::getFieldType(Vector2f position)
{
	if (position.x / scale < mapDimensions.x && position.y / scale < mapDimensions.y) {
		return fields[pair<int, int>(int(position.x / scale),int(position.y / scale))]->getType();
	}
	return 0;
}

int Map::getFieldType(int x, int y)
{
	if (x < mapDimensions.x && y < mapDimensions.y) {
		return fields[pair<int, int>(x, y)]->getType();
	}
	return 0;
}

bool Map::loadTextures()
{
	sf::Image* spriteSheet = new sf::Image();
	if(!spriteSheet->loadFromFile(texturesDir))
	{
		std::cout << "Failed to load FieldsSpriteSheet.PNG\n";
		return false;
	}
	for (int i = 0; i < fieldTypesCount; i++)
	{
		if (!texture[i].loadFromImage(*spriteSheet,
			sf::IntRect(i*50,0,50,50)))
		{
			std::cout << "Failed to read " + std::to_string(i) + ". sprite from FieldsSpriteSheet.PNG\n";
			return false;
		}
	}

}

void Map::setTextures(sf::Texture * texture)
{
	this->texture = texture;
}

Field Map::getField(Vector2f position)
{
	int x = position.x / scale;
	int y = position.y / scale;
	if (x < mapDimensions.x && y < mapDimensions.y) {
		return *fields[pair<int, int>(x, y)];
	}
	return NULL;
}

Field Map::getField(int x, int y)
{
	if (x < mapDimensions.x && y < mapDimensions.y) {
		return *fields[pair<int, int>(x, y)];
	}
	return NULL;
}

Vector2i Map::getMapRange()
{
	return Vector2i(mapDimensions.x, mapDimensions.y);
}

float Map::getUpMoveLimit(FloatRect character)
{
	int L = int(character.left / scale);
	int P = int((character.left + character.width) / scale);
	int y = int(character.top / scale) - 1;

	if (P*scale == character.left + character.width) {
		P--;
	}

	if (y >= 0) {
		for (int x = L; x <= P && x >= 0; x++) {
			if (getField(x, y).isSolid()) {
				return (y + 1)*scale;  ///(y górnej czêœci gracza * size) daje górn¹ granicê pola gdzie znajduje siê góra gracza
			}
		}
	}
	return -1000;
}

float Map::getRightMoveLimit(FloatRect character)
{
	int L = int(character.top / scale);
	int P = int((character.top + character.height) / scale);
	int x = int((character.left + character.width) / scale) + 1;

	if ((x - 1)*scale == character.left + character.width) {
		x--;
	}

	if (P*scale == character.top + character.height) {
		P--;
	}


	if (x < mapDimensions.x) {
		for (int y = L; y <= P && y >= 0; y++) {
			if (getField(x, y).isSolid()) {
				return (x)*scale;
			}
		}
	}

	return scale* mapDimensions.x;
}

float Map::getDownMoveLimit(FloatRect character)
{
	int L = int(character.left / scale);//11
	int P = int((character.left + character.width) / scale);//12

	int y = int((character.top + character.height) / scale) + 1;//11

	if ((y - 1)*scale == character.top + character.height) {
		y--;
	}

	if (P*scale == character.left + character.width) {
		P--;
	}

	if (y < mapDimensions.y) {
		for (int x = L; x <= P && x >= 0; x++) {
			if (getField(x,y).isSolid()) {
				return y*scale;
			}
		}
	}
	return mapDimensions.y*scale;
}

float Map::getLeftMoveLimit(FloatRect character)
{
	int L = int(character.top / scale);
	int P = int((character.top + character.height) / scale);
	int x = int((character.left) / scale) - 1;

	if (P*scale == character.top + character.height) {
		P--;
	}

	if (x >= 0) {
		for (int y = L; y <= P && y >= 0; y++) {
			if (getField(x,y).isSolid()) {
				return (x + 1)*scale;
			}
		}
	}
	return 0;
}

int Map::countFieldsOfType(Field::FieldType type)
{
	int w = 0;
	for (int x = 0; x < getMapRange().x; x++) {
		for (int y = 0; y < getMapRange().y; y++) {
			if (getFieldType(x, y) == type) {
				w++;
			}
		}
	}
	return w;
}

void Map::draw(RenderTarget & target, RenderStates states) const
{
	Transform transform = getTransform();
	target.draw(*background, transform);
	for(auto it: fields)
	{
		target.draw(*it.second, transform);
	}
	/*for (int x = 0; x < mapDimensions.x; x++) {
		for (int y = 0; y < mapDimensions.y; y++) {
			
			if (fields[Vector2i(x, y)].getType() != 0) {
				target.draw(*fields[Vector2i(x, y)], transform);
			}
		}
	}*/
}
