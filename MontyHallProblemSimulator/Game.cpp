#include "Game.h"

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

	mClosedDoor.setTexture(mClosedDoorTexture);
	mClosedDoor.setPosition(100.f, 100.f);
	return true;
}

void Game::Run()
{
	tgui::Gui gui{ mWindow };  // Create the gui and attach it to the window
	
	tgui::Texture closedDoorTexture("C:\\Users\\Jongmin\\Documents\\MontyHallProblemSimulator\\MontyHallProblemSimulator\\closedDoor.png");
	tgui::Picture::Ptr door1 = tgui::Picture::create(closedDoorTexture);
	tgui::Picture::Ptr door2 = tgui::Picture::create(closedDoorTexture);
	tgui::Picture::Ptr door3 = tgui::Picture::create(closedDoorTexture);

	door1->setPosition(150, 160);
	door2->setPosition(500,160);
	door3->setPosition(850, 160);

	gui.add(door1);
	gui.add(door2);
	gui.add(door3);

	door1->connect("Clicked", signalHandler);

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
