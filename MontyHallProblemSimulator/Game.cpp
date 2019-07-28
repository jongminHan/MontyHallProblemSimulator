#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Init()
{
	mWindow.create(sf::VideoMode(WIDTH, HEIGHT), "Monty Hall Problem Simulator");

	if (!mClosedDoorTexture.loadFromFile("C:\\Users\\Jongmin\\Documents\\MontyHallProblemSimulator\\MontyHallProblemSimulator\\closedDoor.png"))
	{
		std::cout << "Cannot load image\n";
		return false;
	}

	mClosedDoor.setTexture(mClosedDoorTexture);
	mClosedDoor.setPosition(100.f, 100.f);
	return true;
}

void Game::Run()
{
	tgui::Gui gui{ mWindow };  // Create the gui and attach it to the window
	
	tgui::Texture closedDoorTexture("C:\\Users\\Jongmin\\Documents\\MontyHallProblemSimulator\\MontyHallProblemSimulator\\closedDoor.png");
	tgui::Picture::Ptr door1 = tgui::Picture::create(closedDoorTexture);
	door1->setPosition(150, 210);
	gui.add(door1);
	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mWindow.close();
			}

			gui.handleEvent(event); // Pass the event to the widgets
		}

		mWindow.clear(sf::Color::White);
		gui.draw(); // Draw all widgets
		mWindow.display();
	}
}
