#pragma once
#include "Field.h"
class BrickWall :
	public Field
{
public:
	BrickWall(float s=0.f, int xx=0, int yy=0);
	~BrickWall();
};

