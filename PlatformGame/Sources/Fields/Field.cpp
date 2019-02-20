#include "Field.h"

float Field::size = 1;

Field::Field(float s, int xx, int yy)
{
	size = s;
	sprite.setPosition(Vector2f(xx*size, yy*size));
	type = Empty;
}

void Field::setPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}

void Field::setTexture(Texture* tex)
{
	sprite.setTexture(tex[type]);
}

Field::FieldType Field::getType() const
{
	return type;
}

void Field::setType(FieldType newType)
{
	type = newType;
}

Vector2f Field::getPosition() const
{
	return sprite.getPosition();
}

void Field::draw(RenderTarget & target, RenderStates states) const
{
	Transform transform = getTransform();
	target.draw(sprite, transform);
}
