#pragma once
#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Global.h"

class Game
{
public:
	Game();
	virtual ~Game();
	bool Init();
	void Run();
private:
	sf::RenderWindow mWindow;
	sf::Texture mClosedDoorTexture;
	sf::Texture mGoatDoorTexture;
};