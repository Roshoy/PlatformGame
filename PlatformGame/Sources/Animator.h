#pragma once
#include <SFML/Graphics.hpp>

class Animator
{
public:
	enum State
	{
		Idle = 0,
		Run = 1,
		Jump = 2,
		Fall = 3		
	};
	Animator();
	void setState(State newState) ;
	void setNextTexture(float vYMax, float vY);
	void setTextures(std::map<Animator::State, std::vector<sf::Texture>>& newTextures) ;
protected:
	void setAnimationSpeed(State s, int speed);
	bool facingRight;
	State state;
	sf::Texture* nextTextureToShow;
	sf::Vector2f textureSize{ 0,0 };
	std::map<State, int> animationSpeeds;
private:
	static int FRAMES_PER_SEC;
	std::map<Animator::State, std::vector<sf::Texture>> textures;
	int textureIdToShow{ 0 };
	int framesPassed{ 0 };

	void setNextTextureJump(float vYMax, float vY);
	void setNextTextureInCycle();
};

