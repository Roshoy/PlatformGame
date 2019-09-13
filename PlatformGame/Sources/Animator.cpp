#include "Animator.h"
#include <iostream>

int Animator::_FRAMES_PER_SEC = 360;

std::map<State, std::string> Animator::_stateName = { {State::Idle, "idle"}, 
	{State::Fall, "fall"}, 
	{State::Jump, "jump"}, 
	{State::Run, "run"} };

Animator::Animator()
{
	_animationSpeeds.insert(std::make_pair(State::Idle, 50));
	_animationSpeeds.insert(std::make_pair(State::Run, 70));
	//_animationSpeeds.insert(std::make_pair(Jump, 50));
	_animationSpeeds.insert(std::make_pair(State::Fall, 100));
}

void Animator::setState(State newState)
{
	if (_state == newState)return;
	_textureIdToShow = 0;
	if(_animationSpeeds[newState] != 0)
		_framesPassed = _FRAMES_PER_SEC/_animationSpeeds[newState];
	_state = newState;
}

void Animator::setNextTexture(float vYMax, float vY)
{	
	_framesPassed++;
	switch(_state)
	{
	case State::Idle:
		setNextTextureInCycle();
		break;
	case State::Run:
		setNextTextureInCycle();
		break;
	case State::Jump:
		setNextTextureJump(vYMax, vY);
		break;
	case State::Fall:
		setNextTextureInCycle();
		break;
	}
	_textureSize = static_cast<sf::Vector2f>(_nextTextureToShow->getSize());
}

void Animator::setTextures(std::map<State, std::vector<sf::Texture>>& newTextures)
{
	_textures = newTextures;
	if (_textures.begin()->second.size() > 0) {
		_nextTextureToShow = &_textures.begin()->second[0];
		
	}
	_textureSize = static_cast<sf::Vector2f>(_nextTextureToShow->getSize());

}

void Animator::setAnimationSpeed(State s, int speed)
{
	_animationSpeeds[s] = speed;
}

void Animator::setNextTextureJump(float vYMax, float vY)
{
	if (_textures.find(State::Jump) == _textures.end())return;
	_textureIdToShow = abs(vY) * _textures[State::Jump].size() / (vYMax+1);
	_nextTextureToShow = &_textures[State::Jump][_textureIdToShow];
}

void Animator::setNextTextureInCycle()
{
	if(_framesPassed >= _FRAMES_PER_SEC / _animationSpeeds[_state])
	{
		_textureIdToShow = (_textureIdToShow + 1) % _textures[_state].size();
		_nextTextureToShow = &_textures[_state][_textureIdToShow];
		_framesPassed = 0;
	}
}
 