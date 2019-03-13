#include "Animator.h"
#include <iostream>

int Animator::FRAMES_PER_SEC = 360;

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
	if(animationSpeeds[newState] != 0)
		framesPassed = FRAMES_PER_SEC/animationSpeeds[newState];
	
	std::cout << "Frames: " << framesPassed<<'\n';
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

void Animator::setAnimationSpeed(State s, int speed)
{
	animationSpeeds[s] = speed;
}

void Animator::setNextTextureJump(float vYMax, float vY)
{
	if (textures.find(Jump) == textures.end())return;
	textureIdToShow = abs(vY) * textures[Jump].size() / (vYMax+1);
	nextTextureToShow = &textures[Jump][textureIdToShow];
}

void Animator::setNextTextureInCycle()
{
	if(framesPassed >= FRAMES_PER_SEC / animationSpeeds[state])
	{
		textureIdToShow = (textureIdToShow + 1) % textures[state].size();
		nextTextureToShow = &textures[state][textureIdToShow];
		framesPassed = 0;
	}
}
 