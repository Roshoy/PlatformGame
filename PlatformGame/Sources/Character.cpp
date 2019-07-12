#include "Character.h"

using namespace std;

unsigned int Character::spriteCount = 8;
unsigned int Character::characterTypesCount = 2;

Character::Character(const sf::Vector2f& scale, CharacterType charName, const sf::Vector2f& size) :Moveable(scale, size)
{		
	characterType = charName;
	hitbox.setSize(sf::Vector2f(size.x*scale.x, size.y*scale.y));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2);
}

Character::CharacterType Character::getCharacterType()
{
	return characterType;
}

void Character::setPosition(const sf::Vector2f& pos)
{
	Moveable::setPosition(pos);
}

void Character::spawn(const sf::Vector2f& pos)
{
	setPosition(pos*Field::fieldSize);
	body.setOrigin(scale.x * textureSize.x / 2, scale.y*textureSize.y - size.y / 2);
}

void Character::spawn(float x, float y)
{	
	setPosition(sf::Vector2f(x*Field::fieldSize, y*Field::fieldSize));
	body.setOrigin(textureSize.x/2 - size.x/(2*body.getScale().x) , textureSize.y-size.y/body.getScale().y - 1);
}


void Character::updateNextPosition(const sf::Vector2f& newPosition)
{
	Moveable::updateNextPosition(newPosition);
	updateTexture(true);
	hitbox.setPosition(getCurrentRect().left, getCurrentRect().top);
}

void Character::updateTexture(bool right)
{
	if (velocity.y == 0) {
		if (velocity.x != 0)
		{
			setState(Run);
		}
		else
		{
			setState(Idle);
		}
	}else if (velocity.y > 0)
	{
		//cout << "Vel.y: " << velocity.y << endl;
		setState(Fall);
	}
	else if (velocity.y < 0)
	{
		setState(Jump);
	}
	setNextTexture(maxVelocity.y, velocity.y);
	body.setTexture(*nextTextureToShow);
	if ((facingRight && velocity.x < 0) || (!facingRight && velocity.x > 0)) {
		facingRight = !facingRight;
		if (!facingRight^right)body.setTextureRect(sf::Rect<int>(0, 0, textureSize.x, textureSize.y));
		else body.setTextureRect(sf::Rect<int>(textureSize.x, 0, -textureSize.x, textureSize.y));
	}
}

void Character::draw(RenderTarget& target, RenderStates states) const
{
	
	sf::Transform transform = getTransform();
	
	target.draw(body, transform);
	//target.draw(hitbox, transform);
}
