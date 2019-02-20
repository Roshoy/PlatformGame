#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Button : public sf::Drawable, public sf::Transformable {
public:
	Button(sf::Vector2f size = sf::Vector2f(0.f,0.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f));
	void setString(std::string s);
	void setFont(sf::Font& f);
	void setTextSize(float s);
	void setTextColor(sf::Color c);
	bool highlighted(sf::RenderWindow & win, sf::Color c);
	void setPosition(sf::Vector2f p);
	void setSize(sf::Vector2f s);
	sf::Vector2f getSize();
	sf::Vector2f getPosition();

private:
	void setTextPosition();
	bool highLight;
	sf::Color color;
	sf::RectangleShape* body;
	sf::Text* text;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;

};