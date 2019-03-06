#include "SpawnPoint.h"
#include "../Player.h"
#include "../Fruk.h"

Character* SpawnPoint::spawn(Character* character)
{
	character->setPosition(getPosition());
	return character;
}

SpawnPoint::~SpawnPoint()
{
}
