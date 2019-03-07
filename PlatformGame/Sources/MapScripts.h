#pragma once
#include <SFML/Graphics.hpp>
class MapScripts
{
public:
	MapScripts();
	std::vector<std::pair<int, int>> frukSpawnPoints;
	std::pair<int,int> playerSpawnPoint;
	void setSpawnPoints();
	std::vector<std::pair<int, int>> winningPoints;
	void setWinningPoints();

};

