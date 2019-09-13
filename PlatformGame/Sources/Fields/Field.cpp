#include "Field.h"

float Field::_fieldSize = 32;
float Field::_textureSize = 16;

Field::Field( int xx, int yy):_type(FieldType::Empty), _unique(false), _typeT(0), _scripted(false)
{
	_sprite.setPosition(Vector2f(xx*_fieldSize, yy*_fieldSize));
	_sprite.setScale(_fieldSize / _textureSize, _fieldSize / _textureSize);
}

void Field::init(float s, int xx, int yy, FieldType type)
{	
	this->_type = type;	
}

void Field::setPosition(Vector2f pos)
{
	_sprite.setPosition(pos);
}

void Field::setTexture(Texture& tex)
{
	_sprite.setTexture(tex);
}

int Field::getType() const
{
	return _typeT;
}

void Field::setType(int newType)
{
	_typeT = newType;
}

bool Field::isSolid()
{
	return _solid;
}

void Field::setSolid(bool solid)
{
	this->_solid = solid;
}

Vector2f Field::getPosition() const
{
	return _sprite.getPosition();
}

bool Field::isUnique()
{
	return _unique;
}

void Field::draw(RenderTarget & target, RenderStates states) const
{
	Transform transform = getTransform();
	target.draw(_sprite, transform);
}
