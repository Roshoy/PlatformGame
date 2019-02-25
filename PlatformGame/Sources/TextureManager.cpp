#include "TextureManager.h"



TextureManager::TextureManager(std::string textureDir)
{
	characterTextures = new sf::Texture*[Character::characterTypesCount];
	fieldTextures = new sf::Texture[Map::fieldTypesCount];
	texturesDir = textureDir;
}


TextureManager::~TextureManager()
{
	for(int i=0; i<Character::characterTypesCount; i++)
	{
		delete[] characterTextures[i];
	}
	delete[] characterTextures;
	delete[] fieldTextures;
}

void TextureManager::setCharacterTextures(Character& character)
{
	character.setTextures(characterTextures[character.getCharacterType()]);
}

void TextureManager::setMapTextures(Map& map)
{
	map.setTextures(fieldTextures);
}

void TextureManager::loadTextures()
{
	loadCharacterTextures("Player", Character::Player);
	loadCharacterTextures("Fruk", Character::Fruk);
	loadFieldTextures();
}

void TextureManager::loadCharacterTextures(string character, Character::CharacterType type)
{
	sf::Image* spriteSheet = new Image();
	spriteSheet->loadFromFile(texturesDir + character +"SpriteSheet.png");
	sf::Texture* textures = new sf::Texture[Character::spriteCount];
	
	for(int i=0;i<Character::spriteCount;i++)
	{
		if(!textures[i].loadFromImage(*spriteSheet,
			sf::IntRect(i*spriteSheet->getSize().x / Character::spriteCount, 0,
			spriteSheet->getSize().x / Character::spriteCount, spriteSheet->getSize().y)))
		{
			std::cout << "Character Texture load fail\n";
		}

	}
	characterTextures[type] = textures;
	delete spriteSheet;
}

void TextureManager::loadFieldTextures()
{
	sf::Image* spriteSheet = new Image();
	if(!spriteSheet->loadFromFile(texturesDir + "FieldsSpriteSheet.png"))
	{
		std::cout << "Failed to load FieldsSpriteSheet.png\n";
	}
	for(int i=0; i<Map::fieldTypesCount; i++)
	{
		if (!fieldTextures[i].loadFromImage(*spriteSheet, sf::IntRect(i*spriteSheet->getSize().y, 0,
			spriteSheet->getSize().y, spriteSheet->getSize().y)))
		{
			std::cout << "Field Texture load fail\n";
		}		
	}

	delete spriteSheet;
}




