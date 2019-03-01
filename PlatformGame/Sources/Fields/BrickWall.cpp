#include "BrickWall.h"



BrickWall::BrickWall(float s, int xx, int yy): Field(s,xx,yy)
{
	solid = true;
	type = Brick;
	unique = false;
}


BrickWall::~BrickWall()
{
}
