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
	Map(float size = 0.f, int x = 1, int y = 1);
	vector <vector <Field>> fields;
	void setField(int x, int y, int type);
	Texture *texture;
	void setMapSize(int x, int y);
	void saveMapFile();
	void loadMapFile();	
	float size;
	int getFieldType(Vector2f position);
	int getFieldType(int x, int y);

	bool loadTextures();

	Field getField(Vector2f position);
	Field getField(int x, int y);

	Vector2i getMapRange();

	float getUpMoveLimit(FloatRect player);
	float getRightMoveLimit(FloatRect player);
	float getDownMoveLimit(FloatRect player);
	float getLeftMoveLimit(FloatRect player);
	
private:
	static std::string texturesDir;
	static int fieldTypesCount;
	RectangleShape* background;
	virtual void draw(RenderTarget &target, RenderStates states)const;


};