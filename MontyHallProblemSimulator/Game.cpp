#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Init()
{
	mWindow.create(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
	return true;
}

void Game::Run()
{
	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mWindow.close();
			}
		}

		mWindow.clear(sf::Color(50, 200, 50));
		//mWindow.draw();
		mWindow.display();
	}
}
