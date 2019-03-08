#include "Animator.h"
#include <iostream>

void Animator::setState(State newState)
{
	if (state == newState)return;
	textureToShow = 0;
	state = newState;
}

void Animator::setNextTexture()
{
	framesPassed++;
	switch (state)
	{
	case Idle:
		if (framesPassed == 10) {
			framesPassed = 0;
			textureToShow++;
			textureToShow %= textures[state].size();
			std::cout << "Idle: " << textureToShow << '\n';
			nextTextureToShow = &textures[state][textureToShow];
		}
		break;
	case Run:
		if (framesPassed == 5) {
			framesPassed = 0;
			textureToShow++;
			textureToShow %= textures[state].size();
			std::cout << "Run: " << textureToShow << '\n';
			nextTextureToShow = &textures[state][textureToShow];
		}
		break;
	case Jump:
		if (framesPassed == 10) {
			framesPassed = 0;
			textureToShow++;
			if (textureToShow < textures[state].size()) {
				std::cout << "Jump: " << textureToShow << '\n';
				nextTextureToShow = &textures[state][textureToShow];
			}
		}
	case Fall:
		if (framesPassed == 10) {
			framesPassed = 0;
			textureToShow++;
			if (textureToShow < textures[state].size()) {
				std::cout << "Fall: " << textureToShow << '\n';
				nextTextureToShow = &textures[state][textureToShow];
			}
		}
		break;
	}
	
	

}

void Animator::setTextures(std::map<Animator::State, std::vector<sf::Texture>>& newTextures)
{
	textures = newTextures;
	if (textures.begin()->second.size() > 0) {
		nextTextureToShow = &textures.begin()->second[0];
	}
	textureSize = static_cast<sf::Vector2f>(nextTextureToShow->getSize());

}
 