#pragma once
#include "Field.h"
class PlayerSpawn :
	public Field
{
public:
	PlayerSpawn(float s = 0.f, int xx = 0, int yy = 0);
	~PlayerSpawn();
};

