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
	std::map<Animator::State, std::vector<sf::Texture>> getPlayerTextures() const;
	std::map<Animator::State, std::vector<sf::Texture>> getFrukTextures() const;
private:
	std::string texturesDir;
	std::map<Animator::State, std::vector<sf::Texture>> playerTextures;
	std::map<Animator::State, std::vector<sf::Texture>> frukTextures;
	std::vector<sf::Texture> fieldTextures;
	void loadCharacterTextures(const std::string& character, int texHeight, int texWidth);
	void loadFrukTextures();
	void loadPlayerTextures();
	void loadFieldTextures();
};

