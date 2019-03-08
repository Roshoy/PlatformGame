#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Map.h"
#include <filesystem>
class TextureManager
{
public:
	TextureManager(std::string textureDir = "Textures/");
	~TextureManager();
	
	void setCharacterTextures(Character& character);
	void setMapTextures(Map& map);
	void loadTextures();
	std::map<Animator::State, std::vector<sf::Texture>>* getPlayerTextures();

private:
	string texturesDir;
	std::map<Animator::State, std::vector<sf::Texture>>* playerTextures;
	sf::Texture* fieldTextures;
	void loadCharacterTextures(string character, Character::CharacterType type);
	void loadPlayerTextures();
	void loadFieldTextures();
};

