#pragma once
#include "Field.h"
#include "../Character.h"

class SpawnPoint :
	public Field
{
public:
	SpawnPoint(int x = 0, int y = 0): Field(x,y){};
	Character* spawn(Character* character);
	~SpawnPoint();
};

