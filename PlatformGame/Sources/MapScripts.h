#pragma once
#include <SFML/Graphics.hpp>
#include "Fields/SpawnPoint.h"
class MapScripts
{
public:
	MapScripts();
	std::vector<pair<int, int>> frukSpawnPoints;
	pair<int,int> playerSpawnPoint;
	void setSpawnPoints();
	std::vector<pair<int, int>> winningPoints;
	void setWinningPoints();

};

