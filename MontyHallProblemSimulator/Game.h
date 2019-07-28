#pragma once
#include <SFML/Graphics.hpp>
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
};