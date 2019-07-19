#include "TextureManager.h"

TextureManager::TextureManager(const std::string& textureDir)
{
	//characterTextures = new sf::Texture*[Character::characterTypesCount];
	playerTextures = std::map<Animator::State, std::vector<sf::Texture>>();
	frukTextures = std::map<Animator::State, std::vector<sf::Texture>>();
	texturesDir = textureDir;
}

void TextureManager::setCharacterTextures(const Character& character)
{
	//character.setTextures(characterTextures[character.getCharacterType()]);
}

void TextureManager::setMapTextures(Map& map)
{
	map.setTextures(fieldTextures);
}

void TextureManager::loadTextures()
{
	loadPlayerTextures();
	loadFrukTextures();
	//loadCharacterTextures("Fruk", Character::Fruk);
	loadFieldTextures();
}

std::map<Animator::State, std::vector<sf::Texture>> TextureManager::getPlayerTextures() const
{
	return playerTextures;
}

std::map<Animator::State, std::vector<sf::Texture>> TextureManager::getFrukTextures() const
{
	return frukTextures;
}

void TextureManager::loadCharacterTextures(const std::string& character, int texHeight, int texWidth)
{
	/*
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
	*/
}

void TextureManager::loadFrukTextures()
{
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tex;
		if(!tex.loadFromFile(texturesDir + "Fruk/slime-idle-" + std::to_string(i) + ".png"))cout<<"FUCKED\n";
		frukTextures[Animator::Idle].push_back(tex);
	}
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tex;
		tex.loadFromFile(texturesDir + "Fruk/slime-move-" + std::to_string(i) + ".png");
		frukTextures[Animator::Run].push_back(tex);
	}
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tex;
		tex.loadFromFile(texturesDir + "Fruk/slime-idle-" + std::to_string(i) + ".png");
		(frukTextures)[Animator::Fall].push_back(tex);
	}
}

void TextureManager::loadPlayerTextures()
{
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tex;
		tex.loadFromFile(texturesDir + "Player/adventurer-idle-0" + std::to_string(i) + ".png");
		(playerTextures)[Animator::Idle].push_back(tex);
	}
	for (int i = 0; i < 6; i++)
	{
		sf::Texture tex;
		tex.loadFromFile(texturesDir + "Player/adventurer-run-0" + std::to_string(i) + ".png");
		(playerTextures)[Animator::Run].push_back(tex);
	}
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tex;
		tex.loadFromFile(texturesDir + "Player/adventurer-jump-0" + std::to_string(i) + ".png");
		(playerTextures)[Animator::Jump].push_back(tex);
	}
	for (int i = 0; i < 2; i++)
	{
		sf::Texture tex;
		tex.loadFromFile(texturesDir + "Player/adventurer-fall-0" + std::to_string(i) + ".png");
		(playerTextures)[Animator::Fall].push_back(tex);
	}

	
}

void TextureManager::loadFieldTextures()
{
	sf::Image spriteSheet = Image();
	if(!spriteSheet.loadFromFile(texturesDir + "Tileset.png"))
	{
		std::cout << "Failed to load Tileset.png\n";
	}
	int sheetWidth = spriteSheet.getSize().x/Field::textureSize;
	int sheetHeight = spriteSheet.getSize().y / Field::textureSize;
	for(int i=0; i<sheetWidth*sheetHeight; i++)
	{
		fieldTextures.push_back(sf::Texture());
		if (!fieldTextures[i].loadFromImage(spriteSheet, sf::IntRect((i % sheetWidth)*(int)Field::textureSize,
			i/sheetWidth * (int)Field::textureSize, Field::textureSize, Field::textureSize)))
		{
			std::cout << "Field Texture load fail on "<<i<<" texture\n";
		}		
	}

}




