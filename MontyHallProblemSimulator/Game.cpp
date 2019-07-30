#include "Game.h"
#include <unordered_map>

Game::Game()
	: mClickNumber(0)
	, mbWin(false)
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

	if (!mCarDoorTexture.loadFromFile("C:\\Users\\Jongmin\\Documents\\MontyHallProblemSimulator\\MontyHallProblemSimulator\\carDoor.png"))
	{
		std::cout << "Cannot load image\n";
		return false;
	}

	mDoor1 = std::make_shared<Door>(mClosedDoorTexture);
	mDoor2 = std::make_shared<Door>(mClosedDoorTexture);
	mDoor3 = std::make_shared<Door>(mClosedDoorTexture);

	return true;
}

void Game::Run()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	tgui::Gui gui{ mWindow };  // Create the gui and attach it to the window
	

	switch (rand() % 3) // True for car. False for goat.
	{
	case 0:
		mDoor1->SetCar(true);
		break;
	case 1:
		mDoor2->SetCar(true);
		break;
	case 2:
		mDoor3->SetCar(true);
		break;
	}

	mDoor1->setPosition(150, 160);
	mDoor2->setPosition(500, 160);
	mDoor3->setPosition(850, 160);

	gui.add(mDoor1);
	gui.add(mDoor2);
	gui.add(mDoor3);

	mDoor1->connect("Clicked", [this]()
		{
			std::cout << "Door 1 is clicked\n";
			mClickNumber++;

			if (mClickNumber < 2)
			{
				if (mDoor1->IsCar())
				{
					switch (rand() % 2)
					{
					case 0:
						mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor2->setEnabled(false);
						break;
					case 1:
						mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor3->setEnabled(false);
						break;
					}
				}
				else if (mDoor2->IsCar())
				{
					mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor3->setEnabled(false);
				}
				else if (mDoor3->IsCar())
				{
					mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor2->setEnabled(false);
				}
			}
			else // if mClickNumber = 2
			{
				if (mDoor1->IsCar())
				{
					mDoor1->getRenderer()->setTexture(mCarDoorTexture);
					mDoor1->setEnabled(false);
				}
				else
				{
					mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor1->setEnabled(false);
				}

				if (mDoor2->IsCar())
				{
					mDoor2->getRenderer()->setTexture(mCarDoorTexture);
					mDoor2->setEnabled(false);
				}
				else
				{
					mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor2->setEnabled(false);
				}

				if (mDoor3->IsCar())
				{
					mDoor3->getRenderer()->setTexture(mCarDoorTexture);
					mDoor3->setEnabled(false);
				}
				else
				{
					mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor3->setEnabled(false);
				}
			}
		});

	mDoor2->connect("Clicked", [this]()
		{
			std::cout << "Door 2 is clicked\n";
			mClickNumber++;

			if (mClickNumber < 2)
			{
				if (mDoor2->IsCar())
				{
					switch (rand() % 2)
					{
					case 0:
						mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor1->setEnabled(false);
						break;
					case 1:
						mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor3->setEnabled(false);
						break;
					}
				}
				else if (mDoor1->IsCar())
				{
					mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor3->setEnabled(false);
				}
				else if (mDoor3->IsCar())
				{
					mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor1->setEnabled(false);
				}
			}
			else // if mClickNumber = 2
			{
				if (mDoor1->IsCar())
				{
					mDoor1->getRenderer()->setTexture(mCarDoorTexture);
					mDoor1->setEnabled(false);
				}
				else
				{
					mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor1->setEnabled(false);
				}

				if (mDoor2->IsCar())
				{
					mDoor2->getRenderer()->setTexture(mCarDoorTexture);
					mDoor2->setEnabled(false);
				}
				else
				{
					mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor2->setEnabled(false);
				}

				if (mDoor3->IsCar())
				{
					mDoor3->getRenderer()->setTexture(mCarDoorTexture);
					mDoor3->setEnabled(false);
				}
				else
				{
					mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor3->setEnabled(false);
				}
			}
		});

	mDoor3->connect("Clicked", [this]()
		{
			std::cout << "Door 3 is clicked\n";
			mClickNumber++;

			if (mClickNumber < 2)
			{
				if (mDoor3->IsCar())
				{
					switch (rand() % 2)
					{
					case 0:
						mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor1->setEnabled(false);
						break;
					case 1:
						mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor2->setEnabled(false);
						break;
					}
				}
				else if (mDoor1->IsCar())
				{
					mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor2->setEnabled(false);
				}
				else if (mDoor2->IsCar())
				{
					mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor1->setEnabled(false);
				}
			}
			else // if mClickNumber = 2
			{
				if (mDoor1->IsCar())
				{
					mDoor1->getRenderer()->setTexture(mCarDoorTexture);
					mDoor1->setEnabled(false);
				}
				else
				{
					mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor1->setEnabled(false);
				}

				if (mDoor2->IsCar())
				{
					mDoor2->getRenderer()->setTexture(mCarDoorTexture);
					mDoor2->setEnabled(false);
				}
				else
				{
					mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor2->setEnabled(false);
				}

				if (mDoor3->IsCar())
				{
					mDoor3->getRenderer()->setTexture(mCarDoorTexture);
					mDoor3->setEnabled(false);
				}
				else
				{
					mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor3->setEnabled(false);
				}
			}
		});

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

	tgui::Label::Ptr label3 = tgui::Label::create();
	label3->setText("You won a car!");
	label3->setSize(167.2, 25.3399);
	label3->setPosition(250, 40);
	label3->setTextSize(18);
	label3->setVisible(false);

	gui.add(label3);

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
