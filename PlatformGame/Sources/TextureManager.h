#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Map.h"
#include <filesystem>
class TextureManager
{
public:
	TextureManager(const std::string& textureDir = "Textures/");
	//~TextureManager(){};
	
	void setCharacterTextures(const Character& character);
	void setMapTextures(Map& map);
	void loadTextures();
	std::map<State, std::vector<sf::Texture>> getCharacterTextures(const Character::CharacterType& charType) const;
private:
	std::string _texturesDir;
	std::map<State, std::vector<sf::Texture>> _playerTextures;
	std::map<State, std::vector<sf::Texture>> _frukTextures;
	std::map<Character::CharacterType, std::map<State, std::vector<sf::Texture>>> _characterTextures;
	std::vector<sf::Texture> _fieldTextures;
	void loadCharacterTextures(const Character::CharacterType& charType, const State& state, int count);
	void loadFrukTextures();
	void loadPlayerTextures();
	void loadFieldTextures();
};

