#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

enum class FieldType
{
	Empty = 0,
	Spawn = 1,
	Script = 2
};

class Field: public Drawable, public Transformable {
public:	
	Field(int xx = 0, int yy = 0);

	void init(float s = 0.f, int xx = 0, int yy = 0, FieldType type = FieldType::Empty);

	void setPosition(Vector2f pos);
	void setTexture(Texture& tex);
	int getType() const;
	void setType(int newType);
	int _typeT; //_characterTextures type TODO: this type defines field
	bool isSolid();
	void setSolid(bool solid);
	Vector2f getPosition() const;

	bool isUnique();
	static float _fieldSize;
	static float _textureSize;
protected:
	
	FieldType _type;
	bool _unique;
	bool _solid;
	
private:
	bool _scripted;
	Sprite _sprite;
	virtual void draw(RenderTarget &target, RenderStates states)const;
};