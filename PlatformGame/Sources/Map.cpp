#include "Map.h"

int Map::fieldTypesCount = 4;
std::string Map::texturesDir = "Textures/Fields/FieldsSpriteSheet.png";

Map::Map(float ssize, int x, int y)
{
	background = new RectangleShape(Vector2f(0, 0));
	background->setFillColor(Color(100, 150, 255));

	size = ssize;
	setMapSize(x, y);
}

void Map::setField(int x, int y, int type)
{
	if (x < 0 || y < 0 || x >= fields.size() || y >= fields[0].size() || fields[x][y].getType() == type) {
		return;
	}
	if (type == 2) {
		for (int xx = 0; xx < fields.size(); xx++) {
			for (int yy = 0; yy < fields[0].size(); yy++) {
				if (fields[xx][yy].getType() == 2) {
					fields[xx][yy].setType(Field::Empty);
					fields[xx][yy].setTexture(texture);
					yy = fields[xx].size();
					xx = fields.size();
				}
			}
		}
	}

	fields[x][y].setType(static_cast<Field::FieldType>(type));
	
	fields[x][y].setTexture(texture);
	
	
}

void Map::setMapSize(int x, int y)
{
	fields.clear();
	background->setSize(Vector2f(x*size, y*size));

	for (int i = 0; i < x; i++) {
		vector<Field>tab;
		for (int j = 0; j < y; j++) {
			tab.push_back(Field(size, i, j));
			tab[j].setType(static_cast<Field::FieldType>(0));
			//tab[j].setTexture(texture);
		}
		fields.push_back(tab);
	}
}

void Map::saveMapFile()
{
	fstream file;
	file.open("MapFile.txt", ios::out | ios::trunc);
	if (!file.good()) {
		cout << "Blad zapisu mapy" << endl;
	}
	file << size << " " << fields.size() << " " << fields[0].size() << "\n";
	if (fields.size() > 0) {
		for (int y = 0; y < fields[0].size(); y++) {
			for (int x = 0; x < fields.size(); x++) {
				file << fields[x][y].getType() << " ";
			}
			if (y != fields[0].size() - 1) {
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
		cout << "Blad zapisu mapy" << endl;
	}
	int x;
	int y;
	file >> size;
	file >> x;
	file >> y;

	setMapSize(x, y);

	if (x > 0 && y > 0) {
		for (y = 0; y < fields[0].size(); y++) {
			for (x = 0; x < fields.size(); x++) {
				int t;
				file >> t;
				setField(x, y, t);
			}
		}
	}

}

int Map::getFieldType(Vector2f position)
{
	if (position.x / size < fields.size() && position.y / size < fields[0].size()) {
		return fields[int(position.x / size)][int(position.y / size)].getType();
	}
	return 0;
}

int Map::getFieldType(int x, int y)
{
	if (x < fields.size() && y < fields[0].size()) {
		return fields[x][y].getType();
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
	int x = position.x / size;
	int y = position.y / size;
	if (x < fields.size() && y < fields[0].size()) {
		return fields[x][y];
	}
	return NULL;
}

Field Map::getField(int x, int y)
{
	if (x < fields.size() && y < fields[0].size()) {
		return fields[x][y];
	}
	return NULL;
}

Vector2i Map::getMapRange()
{
	return Vector2i(fields.size(), fields[0].size());
}

float Map::getUpMoveLimit(FloatRect player)
{
	int L = int(player.left / size);
	int P = int((player.left + player.width) / size);
	int y = int(player.top / size) - 1;

	if (P*size == player.left + player.width) {
		P--;
	}

	if (y >= 0) {
		for (int x = L; x <= P && x >= 0; x++) {
			if (fields[x][y].getType() == 1) {
				return (y + 1)*size;  ///(y górnej czêœci gracza * size) daje górn¹ granicê pola gdzie znajduje siê góra gracza
			}
		}
	}
	return -1000;
}

float Map::getRightMoveLimit(FloatRect player)
{
	int L = int(player.top / size);
	int P = int((player.top + player.height) / size);
	int x = int((player.left + player.width) / size) + 1;

	if ((x - 1)*size == player.left + player.width) {
		x--;
	}

	if (P*size == player.top + player.height) {
		P--;
	}


	if (x < fields.size()) {
		for (int y = L; y <= P && y >= 0; y++) {
			if (fields[x][y].getType() == 1) {
				return (x)*size;
			}
		}
	}

	return size*fields.size();
}

float Map::getDownMoveLimit(FloatRect player)
{
	int L = int(player.left / size);//11
	int P = int((player.left + player.width) / size);//12

	int y = int((player.top + player.height) / size) + 1;//11

	if ((y - 1)*size == player.top + player.height) {
		y--;


	}

	if (P*size == player.left + player.width) {
		P--;

	}

	if (y < fields[0].size()) {
		for (int x = L; x <= P && x >= 0; x++) {
			if (fields[x][y].getType() == 1) {
				return y*size;
			}
		}
	}
	return fields[0].size()*size;
}

float Map::getLeftMoveLimit(FloatRect player)
{
	int L = int(player.top / size);
	int P = int((player.top + player.height) / size);
	int x = int((player.left) / size) - 1;

	if (P*size == player.top + player.height) {
		P--;
	}

	if (x >= 0) {
		for (int y = L; y <= P && y >= 0; y++) {
			if (fields[x][y].getType() == 1) {
				return (x + 1)*size;
			}
		}
	}
	return 0;
}

void Map::draw(RenderTarget & target, RenderStates states) const
{
	Transform transform = getTransform();
	target.draw(*background, transform);
	for (int x = 0; x < fields.size(); x++) {
		for (int y = 0; y < fields[x].size(); y++) {
			if (fields[x][y].getType() != 0) {
				target.draw(fields[x][y], transform);
			}
		}
	}
}
