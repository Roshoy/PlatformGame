#include "TextureManager.h"

TextureManager::TextureManager(const std::string& textureDir)
{
	//characterTextures = new sf::Texture*[Character::_characterTypesCount];
	_playerTextures = std::map<State, std::vector<sf::Texture>>();
	_frukTextures = std::map<State, std::vector<sf::Texture>>();
	_texturesDir = textureDir;
}

void TextureManager::setCharacterTextures(const Character& character)
{
	//character.setTextures(characterTextures[character.getCharacterType()]);
}

void TextureManager::setMapTextures(Map& map)
{
	map.setTextures(_fieldTextures);
}

void TextureManager::loadTextures()
{
	loadPlayerTextures();
	loadFrukTextures();
	loadFieldTextures();
}

std::map<State, std::vector<sf::Texture>> TextureManager::getCharacterTextures(const Character::CharacterType & charType) const
{
	return _characterTextures.at(charType);
}

void TextureManager::loadCharacterTextures(const Character::CharacterType & charType, const State & state, int count)
{
	for (int i = 0; i < count; i++)
	{
		sf::Texture tex;
		if (!tex.loadFromFile(_texturesDir + Character::_CharacterNames[charType] + "/" + Animator::_stateName[state] + std::to_string(i) + ".png")) {
			cout << "FUCKED\n";
		}
		_characterTextures[charType][state].push_back(tex);
	}
}

void TextureManager::loadFrukTextures()
{
	loadCharacterTextures(Character::CharacterType::Fruk, State::Idle, 4);
	loadCharacterTextures(Character::CharacterType::Fruk, State::Run, 4);
	loadCharacterTextures(Character::CharacterType::Fruk, State::Fall, 4);
}

void TextureManager::loadPlayerTextures()
{
	loadCharacterTextures(Character::CharacterType::Player, State::Idle, 4);
	loadCharacterTextures(Character::CharacterType::Player, State::Run, 6);
	loadCharacterTextures(Character::CharacterType::Player, State::Jump, 4);
	loadCharacterTextures(Character::CharacterType::Player, State::Fall, 2);
}

void TextureManager::loadFieldTextures()
{
	sf::Image spriteSheet = Image();
	if(!spriteSheet.loadFromFile(_texturesDir + "Tileset.png"))
	{
		std::cout << "Failed to load Tileset.png\n";
	}
	int sheetWidth = spriteSheet.getSize().x/Field::_textureSize;
	int sheetHeight = spriteSheet.getSize().y / Field::_textureSize;
	for(int i=0; i<sheetWidth*sheetHeight; i++)
	{
		_fieldTextures.push_back(sf::Texture());
		if (!_fieldTextures[i].loadFromImage(spriteSheet, sf::IntRect((i % sheetWidth)*(int)Field::_textureSize,
			i/sheetWidth * (int)Field::_textureSize, Field::_textureSize, Field::_textureSize)))
		{
			std::cout << "Field Texture load fail on "<<i<<" texture\n";
		}		
	}

}




