#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "Fields/Field.h"
#include "Character.h"


class Map : public Drawable, public Transformable {
public:
	Map(int x = 1, int y = 1);
	Field** _fields;
	void setField(int x, int y, int type);
	
	void setMapSize(int x, int y);
	void saveMapFile() const;
	void loadMapFile();	

	void setTextures(const std::vector<sf::Texture>& texture);

	Field getField(const sf::Vector2f& position) const;
	Field getField(int x, int y) const;

	Vector2i getMapRange() const;

	static sf::Vector2i _mapDimensions;
	std::vector<sf::Vector2i> GetSpawnPoints(const Character::CharacterType& type) const;
private:

	bool isSolidTexture(int ind) const;/*
	template<typename T>
	static T createInstance() { return new T(); }
	typedef std::_map<Field::FieldType, Field*(*)()> FieldTypesMap;*/
//FieldTypesMap _fieldTypesMap;
	std::map<Character::CharacterType, std::vector<sf::Vector2i>> _spawnPoints;
	std::vector<sf::Texture> _textures;	//do vector
	sf::RectangleShape _background;
	virtual void draw(RenderTarget &target, RenderStates states)const;


};