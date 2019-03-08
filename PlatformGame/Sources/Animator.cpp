#include "Animator.h"
#include <iostream>

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
		setNextTextureInCycle(50);
		break;
	case Run:
		setNextTextureInCycle(70);
		break;
	case Jump:
		setNextTextureJump(vYMax, vY);
		break;
	case Fall:
		setNextTextureInCycle(100);
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

void Animator::setNextTextureJump(float vYMax, float vY)
{
	
	textureIdToShow = abs(vY) * textures[Jump].size() / (vYMax+1);
	nextTextureToShow = &textures[Jump][textureIdToShow];
}

void Animator::setNextTextureInCycle(int speed)
{
	if(framesPassed >= 360 / speed)
	{
		textureIdToShow = (textureIdToShow + 1) % textures[state].size();
		nextTextureToShow = &textures[state][textureIdToShow];
		framesPassed = 0;
	}
}
 