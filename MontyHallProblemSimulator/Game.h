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
	sf::Texture mCarDoorTexture;
	std::shared_ptr<Door> mDoor1;
	std::shared_ptr<Door> mDoor2;
	std::shared_ptr<Door> mDoor3;
	int mClickNumber;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	bool mbWin;
};