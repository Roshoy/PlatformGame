#include "Field.h"

float Field::fieldSize = 32;
float Field::textureSize = 16;

Field::Field( int xx, int yy)
{
	
	sprite.setPosition(Vector2f(xx*fieldSize, yy*fieldSize));
	sprite.setScale(fieldSize / textureSize, fieldSize / textureSize);
	type = Empty;
	unique = false;
}

void Field::init(float s, int xx, int yy, FieldType type)
{	
	this->type = type;	
}

void Field::setPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}

void Field::setTexture(Texture& tex)
{
	sprite.setTexture(tex);
}

Field::FieldType Field::getType() const
{
	return type;
}

void Field::setType(FieldType newType)
{
	type = newType;
}

bool Field::isSolid()
{
	return solid;
}

void Field::setSolid(bool solid)
{
	this->solid = solid;
}

Vector2f Field::getPosition() const
{
	return sprite.getPosition();
}

bool Field::isUnique()
{
	return unique;
}

void Field::draw(RenderTarget & target, RenderStates states) const
{
	Transform transform = getTransform();
	target.draw(sprite, transform);
}
