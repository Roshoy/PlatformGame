#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Button.h"

class Menu {
public:
	Menu(sf::RenderWindow& win, sf::Font& f, const sf::Vector2f& bSize = sf::Vector2f(300.f, 100.f), float fSize = 50);
	sf::Vector2f _buttonSize;
	float _fontSize;
	void addButton(const std::string& ss);
	int runMenu();
	void setTitle(const std::string& t);
private:
	sf::Text _title;
	sf::Font& _font;
	sf::RenderWindow& _window;
	std::vector<Button> _button;
	void centerButtons();
	

};