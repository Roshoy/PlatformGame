#pragma once
#include "AbstractFieldScriptStrategy.h"
#include "../Player.h"
#include "../Game.h"

class JumpScript : public FieldScriptStrategy
{
public:
	JumpScript(Player& player) : _player(player) {}
	void execute() override { _player.jump(); }

private:
	Player& _player;
};

class WinScript : public FieldScriptStrategy
{
public:
	void execute() override {};
private:
	GameState& 
};
