#pragma once
#include <SFML/Graphics.hpp>

enum class State
{
	Idle = 0,
	Run = 1,
	Jump = 2,
	Fall = 3
};

class Animator
{
public:

	static std::map<State, std::string> _stateName;
	Animator();
	void setState(State newState) ;
	void setNextTexture(float vYMax, float vY);
	void setTextures(std::map<State, std::vector<sf::Texture>>& newTextures) ;
protected:
	void setAnimationSpeed(State s, int speed);
	bool _facingRight;
	State _state;
	sf::Texture* _nextTextureToShow;
	sf::Vector2f _textureSize{ 0,0 };
	std::map<State, int> _animationSpeeds;
private:
	static int _FRAMES_PER_SEC;
	std::map<State, std::vector<sf::Texture>> _textures;
	int _textureIdToShow{ 0 };
	int _framesPassed{ 0 };

	void setNextTextureJump(float vYMax, float vY);
	void setNextTextureInCycle();
};

