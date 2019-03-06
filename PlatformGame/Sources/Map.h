#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Fields/Field.h"
#include <fstream>

using namespace sf;
using namespace std;

class Map : public Drawable, public Transformable {
public:
	Map(int x = 1, int y = 1);
	Field*** fields;
	vector<Field> spawnPoints;
	void setField(int x, int y, int type);
	
	void setMapSize(int x, int y);
	void saveMapFile();
	void loadMapFile();	

	void setTextures(sf::Texture* texture);

	Field getField(Vector2f position);
	Field getField(int x, int y);

	Vector2i getMapRange();

	static sf::Vector2i mapDimensions;

private:

	bool isSolidTexture(int ind);
	template<typename T>
	static Field * createInstance() { return new T(); }
	typedef std::map<Field::FieldType, Field*(*)()> FieldTypesMap;
	FieldTypesMap fieldTypesMap;

	sf::Texture *texture;	
	sf::RectangleShape* background;
	virtual void draw(RenderTarget &target, RenderStates states)const;


};