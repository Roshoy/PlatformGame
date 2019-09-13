#include "Character.h"
#include "Fields/Field.h"

using namespace std;

unsigned int Character::_spriteCount = 8;
unsigned int Character::_characterTypesCount = 2;
std::map<Character::CharacterType, std::string> Character::_CharacterNames = { {Character::CharacterType::Player, "player"}, {Character::CharacterType::Fruk, "fruk"} };

Character::Character(const sf::Vector2f& scale, CharacterType charName, const sf::Vector2f& size) :Moveable(scale, size)
{		
	_characterType = charName;
	_hitbox.setSize(sf::Vector2f(size.x*scale.x, size.y*scale.y));
	_hitbox.setFillColor(sf::Color::Transparent);
	_hitbox.setOutlineColor(sf::Color::Red);
	_hitbox.setOutlineThickness(2);
}

Character::CharacterType Character::getCharacterType() const
{
	return _characterType;
}

void Character::setPosition(const sf::Vector2f& pos)
{
	Moveable::setPosition(pos);
}

void Character::spawn(const sf::Vector2f& pos)
{
	setPosition(pos * Field::_fieldSize);
	_body.setOrigin(_scale.x * _textureSize.x / 2, _scale.y*_textureSize.y - _size.y / 2);
}

void Character::spawn(float x, float y)
{	
	setPosition(sf::Vector2f(x*Field::_fieldSize, y*Field::_fieldSize));
	_body.setOrigin(_textureSize.x/2 - _size.x/(2*_body.getScale().x) , _textureSize.y-_size.y/_body.getScale().y - 1);
}


void Character::updateNextPosition(const sf::Vector2f& newPosition)
{
	Moveable::updateNextPosition(newPosition);
	updateTexture(true);
	_hitbox.setPosition(getCurrentRect().left, getCurrentRect().top);
}

void Character::updateTexture(bool right)
{
	if (_velocity.y == 0) {
		if (_velocity.x != 0)
		{
			setState(State::Run);
		}
		else
		{
			setState(State::Idle);
		}
	}else if (_velocity.y > 0)
	{
		//cout << "Vel.y: " << _velocity.y << endl;
		setState(State::Fall);
	}
	else if (_velocity.y < 0)
	{
		setState(State::Jump);
	}
	setNextTexture(_maxVelocity.y, _velocity.y);
	_body.setTexture(*_nextTextureToShow);
	if ((_facingRight && _velocity.x < 0) || (!_facingRight && _velocity.x > 0)) {
		_facingRight = !_facingRight;
		if (!_facingRight^right)_body.setTextureRect(sf::Rect<int>(0, 0, _textureSize.x, _textureSize.y));
		else _body.setTextureRect(sf::Rect<int>(_textureSize.x, 0, -_textureSize.x, _textureSize.y));
	}
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	sf::Transform transform = getTransform();
	
	target.draw(_body, transform);
	target.draw(_hitbox, transform);
}
