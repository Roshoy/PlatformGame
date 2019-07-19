#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Field: public Drawable, public Transformable {
public:
	enum FieldType
	{
		Empty = 0,		
		Spawn = 1,
		Script = 2
	};
	
	Field(int xx = 0, int yy = 0);

	void init(float s = 0.f, int xx = 0, int yy = 0, FieldType type = Empty);

	void setPosition(Vector2f pos);
	void setTexture(Texture& tex);
	int getType() const;
	void setType(int newType);
	int typeT; //textures type TODO: this type defines field
	bool isSolid();
	void setSolid(bool solid);
	Vector2f getPosition() const;

	bool isUnique();
	static float fieldSize;
	static float textureSize;
protected:
	
	FieldType type;
	bool unique;
	bool solid;
	
private:
	bool scripted;
	Sprite sprite;
	virtual void draw(RenderTarget &target, RenderStates states)const;
};