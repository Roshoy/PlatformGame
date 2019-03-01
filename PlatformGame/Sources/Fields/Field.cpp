#include "Field.h"

Field::Field(float s, int xx, int yy)
{
	size = s;
	sprite.setPosition(Vector2f(xx*size, yy*size));
	type = Empty;
	unique = false;
}

void Field::init(float s, int xx, int yy, FieldType type)
{
	size = s;
	sprite.setPosition(Vector2f(xx*size, yy*size));
	this->type = type;
}

void Field::setPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}

void Field::setTexture(Texture* tex)
{
	if (tex == nullptr)std::cout << "Given tex array is null\n";
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

bool Field::isSolid()
{
	return solid;
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
