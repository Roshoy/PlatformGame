#include "Menu.h"

Menu::Menu(RenderWindow & win, Font & f, Vector2f bSize, float fSize)
{
	window = &win;
	font = &f;
	buttonSize = bSize;
	fontSize = fSize;
}

void Menu::addButton(string ss)
{
	Button b(buttonSize);
	b.setString(ss);
	b.setFont(*font);
	b.setTextSize(fontSize);
	button.push_back(b);
	
	centerButtons();
}

int Menu::runMenu()
{

	while (window->isOpen()) {
		Event event;
		if (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
				return button.size() - 1;
			}

		}
		
		for (int i = 0; i < button.size(); i++) {
			if (button[i].highlighted(*window, Color::Blue) && Mouse::isButtonPressed(Mouse::Left)) {
				cout << i << " przycisk\n";
				return i;
			}
		}

		window->setView(window->getDefaultView());
		window->clear();
		for (int i = 0; i < button.size(); i++) {
			window->draw(button[i]);
		}
		window->draw(*title);
		window->display();
	}
	return button.size()-1;
}

void Menu::setTitle(string t)
{
	title = new Text(t, *font, fontSize);
	title->setPosition(window->getSize().x / 2 - title->getLocalBounds().width / 2, 100.f);
}

void Menu::centerButtons()
{
	float gap = (window->getSize().y - button.size() * buttonSize.y - 100.f - fontSize) / (button.size() + 1);
	cout << gap << endl;
	for (int i = 0; i < button.size(); i++) {
		button[i].setPosition(Vector2f((window->getSize().x - buttonSize.x) / 2, 100.f + fontSize + (i + 1)*gap + buttonSize.y*i));
	}
}
