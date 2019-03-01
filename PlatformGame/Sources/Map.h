#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Fields/Field.h"
#include "Fields/BrickWall.h"
#include "Fields/PlayerSpawn.h"
#include <fstream>

using namespace sf;
using namespace std;

class Map : public Drawable, public Transformable {
public:
	Map(float size = 0.f, int x = 1, int y = 1);
	Field*** field;
	std::map<pair<int,int>, Field*> fields;
	void setField(int x, int y, int type);
	
	void setMapSize(int x, int y);
	void saveMapFile();
	void loadMapFile();	
	float scale;
	int getFieldType(Vector2f position);
	int getFieldType(int x, int y);

	bool loadTextures();
	void setTextures(sf::Texture* texture);

	Field getField(Vector2f position);
	Field getField(int x, int y);

	Vector2i getMapRange();

	float getUpMoveLimit(FloatRect character);
	float getRightMoveLimit(FloatRect character);
	float getDownMoveLimit(FloatRect character);
	float getLeftMoveLimit(FloatRect character);

	static int fieldTypesCount;

	int countFieldsOfType(Field::FieldType type);
private:
	template<typename T>
	static Field * createInstance() { return new T(); }
	typedef std::map<Field::FieldType, Field*(*)()> FieldTypesMap;
	FieldTypesMap fieldTypesMap;

	sf::Vector2i mapDimensions;
	sf::Texture *texture;
	static std::string texturesDir;	
	sf::RectangleShape* background;
	virtual void draw(RenderTarget &target, RenderStates states)const;


};