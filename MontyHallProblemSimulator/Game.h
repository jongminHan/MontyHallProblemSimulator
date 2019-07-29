#pragma once
#include <iostream>
#include "Door.h"

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
	Door* mDoor1;
	Door* mDoor2;
	Door* mDoor3;
	int mClick;

	const int WIDTH = 1280;
	const int HEIGHT = 720;
};