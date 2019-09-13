#include "Menu.h"

Menu::Menu(sf::RenderWindow& win, sf::Font& f, const sf::Vector2f& bSize, float fSize):
	_window(win),
	_font(f),
	_buttonSize(bSize),
	_fontSize(fSize)
{
}

void Menu::addButton(const std::string& ss)
{
	Button b(_buttonSize);
	b.setString(ss);
	b.setFont(_font);
	b.setTextSize(_fontSize);
	_button.push_back(b);
	
	centerButtons();
}

int Menu::runMenu()
{
	while (_window.isOpen()) {
		sf::Event event;
		if (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_window.close();
				return _button.size() - 1;
			}
		}
		
		for (int i = 0; i < _button.size(); i++) {
			if (_button[i].highlighted(_window, sf::Color::Blue) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				//std::cout << i << " przycisk\n";
				return i;
			}
		}

		_window.setView(_window.getDefaultView());
		_window.clear();
		for (const auto& button : _button)
		{
			_window.draw(button);
		}
		_window.draw(_title);
		_window.display();
	}
	return _button.size()-1;
}

void Menu::setTitle(const std::string& t)
{
	_title = sf::Text(t, _font, _fontSize);
	_title.setPosition(_window.getSize().x / 2 - _title.getLocalBounds().width / 2, 100.f);
}

void Menu::centerButtons()
{
	float gap = (_window.getSize().y - _button.size() * _buttonSize.y - 100.f - _fontSize) / (_button.size() + 1);
	//std::cout << gap << std::endl;
	for (int i = 0; i < _button.size(); i++) {
		_button[i].setPosition(sf::Vector2f((_window.getSize().x - _buttonSize.x) / 2, 100.f + _fontSize + (i + 1)*gap + _buttonSize.y*i));
	}
}
