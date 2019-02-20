#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Button.h"

using namespace std;
using namespace sf;

class Menu {
public:
	Menu(RenderWindow& win, Font& f, Vector2f bSize = Vector2f(300.f, 100.f), float fSize = 50);
	Vector2f buttonSize;
	float fontSize;
	void addButton(string ss);
	int runMenu();
	void setTitle(string t);
private:
	Text* title;
	Font* font;
	RenderWindow* window;
	vector<Button> button;
	void centerButtons();
	

};