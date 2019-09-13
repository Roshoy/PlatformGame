#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Button : public sf::Drawable, public sf::Transformable {
public:
	Button(const sf::Vector2f& size = sf::Vector2f(0.f,0.f),const sf::Vector2f& pos = sf::Vector2f(0.f, 0.f));
	void setString(const std::string& s);
	void setFont(const sf::Font& f);
	void setTextSize(float s);
	void setTextColor(const sf::Color& c);
	bool highlighted(const sf::RenderWindow & win, const sf::Color& c);
	void setPosition(const sf::Vector2f& p);
	void setSize(const sf::Vector2f& s);
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;

private:
	void setTextPosition();
	bool highLight;
	sf::Color color;
	sf::RectangleShape body;
	sf::Text text;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;

};