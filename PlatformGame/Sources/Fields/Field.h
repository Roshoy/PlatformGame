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
		Brick = 1,
		PlayerSpawn = 2,
		FrukSpawn = 3
	};
	static float size;
	Field(float s = 0.f, int xx = 0, int yy = 0);
	bool solid;
	void setPosition(Vector2f pos);
	void setTexture(Texture* tex);
	FieldType getType() const;
	void setType(FieldType newType);
	
	
	Vector2f getPosition() const;
protected:
	FieldType type;

private:
	
	Sprite sprite;
	virtual void draw(RenderTarget &target, RenderStates states)const;
};