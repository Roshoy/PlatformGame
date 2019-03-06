#include "MapScripts.h"
#include "Fruk.h"


MapScripts::MapScripts()
{
	setSpawnPoints();
}

void MapScripts::setSpawnPoints()
{
	int spawnPointCount = 2;
	int xy[] = {5,0,6,0};
	Fruk enemies[] = {
		Fruk(),
		Fruk()
	}; //...
	for(int i=0;i/2<spawnPointCount;i+=2)
	{
		frukSpawnPoints.push_back(pair<int, int>(xy[i], xy[i + 1]));
	}

	playerSpawnPoint = pair<int,int>(0,0);
}

void MapScripts::setWinningPoints()
{
	int winningPointCount = 1;
	int xy[] = {10,5};

	for (int i = 0; i / 2 < winningPointCount; i += 2)
	{
		winningPoints.push_back(pair<int, int>(xy[i], xy[i + 1]));
	}
}


