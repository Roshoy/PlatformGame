#include "Moveable.h"
#include "Animator.h"
#include <iostream>

Moveable::Moveable(sf::Vector2f scale, sf::Vector2f size)
{
	_body = sf::Sprite();

	_body.setScale(scale);
	
	_nextPosition = _body.getPosition();

	_inAir = true;
	this->_scale = scale;
	this->_size = size;
	this->_size.x *= scale.x;
	this->_size.y *= scale.y;

	_velocity = sf::Vector2f(0, 0);
	_maxVelocity = sf::Vector2f(10, 23);

	_acceleration = 2;
	_retardation = 0.5;
}


sf::FloatRect Moveable::getCurrentRect() const
{
	return sf::FloatRect(_body.getPosition().x, _body.getPosition().y, _size.x, _size.y);
}

sf::FloatRect Moveable::getNextRect() const
{
	return sf::FloatRect(_nextPosition, _size);
}


sf::Vector2f Moveable::getSize() const
{
	return _size;
}

sf::Vector2f Moveable::getPosition() const
{
	return _body.getPosition();
}

sf::Vector2f Moveable::getMaxSpeed() const
{
	return sf::Vector2f(_maxVelocity.x - _retardation, _maxVelocity.y);
}

sf::Vector2f Moveable::getMaxAcceleration() const 
{
	return sf::Vector2f(_acceleration - _retardation, GRAVITATION);
}

sf::Vector2f Moveable::getSpeed() const
{
	return _velocity;
}

void Moveable::setPosition(sf::Vector2f pos)
{
	_body.setPosition(pos);
	_nextPosition = pos;	
}

void Moveable::updateNextPosition(const sf::Vector2f& newPosition)
{
	
	if(newPosition.x != _nextPosition.x)
	{
		_velocity.x = 0;
	}
	if (newPosition.y != _nextPosition.y) {
		_velocity.y = 0;
		if (newPosition.y < _nextPosition.y && newPosition.y >= 0)
		{
			_inAir = false;
		}
	}
	_nextPosition = newPosition;
}

void Moveable::updatePosition()
{	
	_body.setPosition(_nextPosition);
}

void Moveable::updateSpeed(const sf::Vector2i & direction)
{
	if (_velocity.x*direction.x < _maxVelocity.x) {
		_velocity.x += _acceleration * direction.x;
	}
	if (_velocity.x*direction.x > _maxVelocity.x) {
		_velocity.x = _maxVelocity.x*direction.x;
	}
	if (_velocity.x >= _retardation) {
		_velocity.x -= _retardation;
	}
	else if (_velocity.x <= -_retardation) {
		_velocity.x += _retardation;
	}
	else
	{
		_velocity.x = 0;
	}
	_velocity.y += GRAVITATION;
	if (_velocity.y > _maxVelocity.y)_velocity.y = _maxVelocity.y;
	if (_velocity.y < -_maxVelocity.y)_velocity.y = -_maxVelocity.y;
		
	if (direction.y < 0) jump();

	_nextPosition += _velocity;
}


void Moveable::jump()
{
	if (!_inAir) {		
		_inAir = true;
		_velocity.y = -_maxVelocity.y;
	}
}

void Moveable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Transform transform = getTransform();
	target.draw(_body, transform);
}
