#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos)
{
	body = new sf::RectangleShape;
	text = new sf::Text;
	color = sf::Color::White;
	body->setSize(size);
	body->setPosition(pos);
	body->setOutlineThickness(3.f);
	body->setOutlineColor(sf::Color::White);
	body->setFillColor(sf::Color::Black);

}

void Button::setString(std::string s)
{
	text->setString(s);
	setTextPosition();
}

void Button::setFont(sf::Font & f)
{
	text->setFont(f);
	setTextPosition();
}

void Button::setTextSize(float s)
{
	text->setCharacterSize(s);
	setTextPosition();
}

void Button::setTextColor(sf::Color c)
{
	text->setOutlineColor(c);
	body->setOutlineColor(c);
	color = c;
}

bool Button::highlighted(sf::RenderWindow & win, sf::Color c)
{
	float mx = sf::Mouse::getPosition(win).x;
	float my = sf::Mouse::getPosition(win).y;


	if (mx <= body->getPosition().x + body->getSize().x &&
		mx >= body->getPosition().x &&
		my <= body->getPosition().y + body->getSize().y &&
		my >= body->getPosition().y) {
		if (!highLight) {			
			text->setFillColor(c);
			body->setOutlineColor(c);
			highLight = true;
		}		
		return true;
	}
	if (highLight) {
		text->setFillColor(color);
		body->setOutlineColor(color);
		highLight = false;
	}
	
	return false;
}

void Button::setPosition(sf::Vector2f p)
{
	body->setPosition(p);
	setTextPosition();
}

void Button::setSize(sf::Vector2f s)
{
	body->setSize(s);
	setTextPosition();
}

sf::Vector2f Button::getSize()
{
	return body->getSize();
}

sf::Vector2f Button::getPosition()
{
	return body->getPosition();
}

void Button::setTextPosition()
{
	sf::FloatRect rect = text->getLocalBounds();
	text->setOrigin(sf::Vector2f(rect.left + (rect.width / 2.0f), rect.top + (rect.height / 2.0f)));
	text->setPosition(getPosition().x + getSize().x / 2, getPosition().y + getSize().y / 2);
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Transform transform = getTransform();
	target.draw(*body, transform);
	target.draw(*text, transform);

}

