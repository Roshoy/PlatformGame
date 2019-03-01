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
		FrukSpawn = 3,
		Win = 4
	};
	
	Field(float s = 0.f, int xx = 0, int yy = 0);

	void init(float s = 0.f, int xx = 0, int yy = 0, FieldType type = Empty);

	void setPosition(Vector2f pos);
	void setTexture(Texture* tex);
	FieldType getType() const;
	void setType(FieldType newType);
	
	bool isSolid();

	Vector2f getPosition() const;

	bool isUnique();
protected:
	FieldType type;
	float size;
	bool unique;
	bool solid;
private:
	
	Sprite sprite;
	virtual void draw(RenderTarget &target, RenderStates states)const;
};