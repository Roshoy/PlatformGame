#include "Animator.h"
#include <iostream>

Animator::Animator()
{
	animationSpeeds.insert(std::make_pair(Idle, 50));
	animationSpeeds.insert(std::make_pair(Run, 70));
	//animationSpeeds.insert(std::make_pair(Jump, 50));
	animationSpeeds.insert(std::make_pair(Fall, 100));
}

void Animator::setState(State newState)
{
	if (state == newState)return;
	textureIdToShow = 0;
	state = newState;
}

void Animator::setNextTexture(float vYMax, float vY)
{	
	framesPassed++;
	switch(state)
	{
	case Idle:
		setNextTextureInCycle();
		break;
	case Run:
		setNextTextureInCycle();
		break;
	case Jump:
		setNextTextureJump(vYMax, vY);
		break;
	case Fall:
		setNextTextureInCycle();
		break;
	}
	textureSize = static_cast<sf::Vector2f>(nextTextureToShow->getSize());
}

void Animator::setTextures(std::map<Animator::State, std::vector<sf::Texture>>& newTextures)
{
	textures = newTextures;
	if (textures.begin()->second.size() > 0) {
		nextTextureToShow = &textures.begin()->second[0];
		
	}
	textureSize = static_cast<sf::Vector2f>(nextTextureToShow->getSize());

}

void Animator::setNextTextureJump(float vYMax, float vY)
{
	
	textureIdToShow = abs(vY) * textures[Jump].size() / (vYMax+1);
	nextTextureToShow = &textures[Jump][textureIdToShow];
}

void Animator::setNextTextureInCycle()
{
	if(framesPassed >= 360 / animationSpeeds[state])
	{
		textureIdToShow = (textureIdToShow + 1) % textures[state].size();
		nextTextureToShow = &textures[state][textureIdToShow];
		framesPassed = 0;
	}
}
 