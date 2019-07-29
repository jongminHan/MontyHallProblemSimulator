#include "Game.h"
#include <unordered_map>

void signalHandler()
{
	std::cout << "clicked\n";
}

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

	if (!mGoatDoorTexture.loadFromFile("C:\\Users\\Jongmin\\Documents\\MontyHallProblemSimulator\\MontyHallProblemSimulator\\goatDoor.png"))
	{
		std::cout << "Cannot load image\n";
		return false;
	}

	mDoor1 = std::make_shared<Door>(mClosedDoorTexture);
	mDoor2 = std::make_shared<Door>(mClosedDoorTexture);
	mDoor3 = std::make_shared<Door>(mClosedDoorTexture);

	return true;
}

void SignalHandler()
{

}

void Game::Run()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	tgui::Gui gui{ mWindow };  // Create the gui and attach it to the window
	

	std::unordered_map<std::shared_ptr<Door>, bool> doorMap = { {mDoor1, false}, {mDoor2, false}, {mDoor3, false} };

	switch (rand() % 3) // true means car. false means goat.
	{
	case 0:
		doorMap[mDoor1] = true;
		break;
	case 1:
		doorMap[mDoor2] = true;
		break;
	case 2:
		doorMap[mDoor3] = true;
		break;
	}

	mDoor1->setPosition(150, 160);
	mDoor2->setPosition(500, 160);
	mDoor3->setPosition(850, 160);

	gui.add(mDoor1);
	gui.add(mDoor2);
	gui.add(mDoor3);

	mDoor1->connect("Clicked", SignalHandler);
/*
	mDoor1->connect("Clicked", [&doorMap, &door1, &door2, &door3, this]()
		{
			std::cout << "Door 1 is clicked\n";
			if (doorMap[door1] == true)
			{
				switch (rand() % 2)
				{
				case 0:
					door2->getRenderer()->setTexture(mGoatDoorTexture);
					break;
				case 1:
					door3->getRenderer()->setTexture(mGoatDoorTexture);
					break;
				}
			}
			else if (doorMap[door2] == true)
			{
				door3->getRenderer()->setTexture(mGoatDoorTexture);
			}
			else if (doorMap[door3] == true)
			{
				door2->getRenderer()->setTexture(mGoatDoorTexture);
			}
		});

	door2->connect("Clicked", [&doorMap, &door1, &door2, &door3, this]()
		{
			std::cout << "Door 2 is clicked\n";
			if (doorMap[door2] == true)
			{
				switch (rand() % 2)
				{
				case 0:
					door1->getRenderer()->setTexture(mGoatDoorTexture);
					break;
				case 1:
					door3->getRenderer()->setTexture(mGoatDoorTexture);
					break;
				}
			}
			else if (doorMap[door1] == true)
			{
				door3->getRenderer()->setTexture(mGoatDoorTexture);
			}
			else if (doorMap[door3] == true)
			{
				door1->getRenderer()->setTexture(mGoatDoorTexture);
			}
		});

	door3->connect("Clicked", [&doorMap, &door1, &door2, &door3, this]()
		{
			std::cout << "Door 2 is clicked\n";
			if (doorMap[door3] == true)
			{
				switch (rand() % 2)
				{
				case 0:
					door1->getRenderer()->setTexture(mGoatDoorTexture);
					break;
				case 1:
					door2->getRenderer()->setTexture(mGoatDoorTexture);
					break;
				}
			}
			else if (doorMap[door1] == true)
			{
				door2->getRenderer()->setTexture(mGoatDoorTexture);
			}
			else if (doorMap[door2] == true)
			{
				door1->getRenderer()->setTexture(mGoatDoorTexture);
			}
		});
*/
	tgui::Label::Ptr label1 = tgui::Label::create();
	label1->setText("Run simulation");
	label1->setSize(167.2, 48);
	label1->setPosition(90, 560);
	label1->setTextSize(18);

	gui.add(label1);

	tgui::Label::Ptr label2 = tgui::Label::create();
	label2->setText("times.    And");
	label2->setSize(127.2, 38);
	label2->setPosition(450, 560);
	label2->setTextSize(18);

	gui.add(label2);

	tgui::ComboBox::Ptr repeatNum = tgui::ComboBox::create();
	repeatNum->addItem("10");
	repeatNum->addItem("50");
	repeatNum->addItem("100");
	repeatNum->addItem("500");
	repeatNum->addItem("10000");
	repeatNum->setPosition(270, 560);
	repeatNum->setSize(160, 22);
	repeatNum->setTextSize(18);

	tgui::ComboBox::Ptr choice = tgui::ComboBox::create();
	choice->addItem("Keep the choice.");
	choice->addItem("Change the choice.");
	choice->setPosition(600, 560);
	choice->setSize(200, 22);
	choice->setTextSize(18);

	gui.add(repeatNum);
	gui.add(choice);

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
