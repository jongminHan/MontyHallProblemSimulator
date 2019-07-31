#include "Game.h"
#include <unordered_map>


Game::Game()
	: mClickNumber(0)
	, mCarNumber(0)
	, mGoatNumber(0)
	, mbWin(false)
{
}

Game::~Game()
{
}

bool Game::Init()
{
	mWindow.create(sf::VideoMode(WIDTH, HEIGHT), "Monty Hall Problem Simulator");
	mGui = std::make_shared<tgui::Gui>(mWindow); // Create the gui and attach it to the window

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


	mDoor1->setPosition(150, 160);
	mDoor2->setPosition(500, 160);
	mDoor3->setPosition(850, 160);

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
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
	return true;
}

void Game::Run()
{
	mGui->add(mDoor1);
	mGui->add(mDoor2);
	mGui->add(mDoor3);

	mDoor1->connect("Clicked", &Game::SignalHandler1, this);
	mDoor2->connect("Clicked", &Game::SignalHandler2, this);
	mDoor3->connect("Clicked", &Game::SignalHandler3, this);

	tgui::Label::Ptr label1 = tgui::Label::create();
	label1->setText("Run simulation");
	label1->setSize(167.2, 48);
	label1->setPosition(90, 560);
	label1->setTextSize(18);

	mGui->add(label1);

	tgui::Label::Ptr label2 = tgui::Label::create();
	label2->setText("times.    And");
	label2->setSize(127.2, 38);
	label2->setPosition(450, 560);
	label2->setTextSize(18);

	mGui->add(label2);

	tgui::Label::Ptr winMessage = tgui::Label::create();
	winMessage->setText("");
	winMessage->setSize(387.2, 46.5575);
	winMessage->setPosition(250, 40);
	winMessage->setTextSize(18);

	mGui->add(winMessage);


	tgui::ComboBox::Ptr repeatNumBox = tgui::ComboBox::create();
	repeatNumBox->addItem("10");
	repeatNumBox->addItem("50");
	repeatNumBox->addItem("100");
	repeatNumBox->addItem("500");
	repeatNumBox->addItem("10000");
	repeatNumBox->setPosition(270, 560);
	repeatNumBox->setSize(160, 22);
	repeatNumBox->setTextSize(18);

	tgui::ComboBox::Ptr choiceBox = tgui::ComboBox::create();
	choiceBox->addItem("Keep the choice.");
	choiceBox->addItem("Change the choice.");
	choiceBox->setPosition(600, 560);
	choiceBox->setSize(200, 22);
	choiceBox->setTextSize(18);

	mGui->add(repeatNumBox);
	mGui->add(choiceBox);

	tgui::Label::Ptr carLabel = tgui::Label::create();
	carLabel->setText("Car: " + std::to_string(mCarNumber));
	carLabel->setPosition(930, 560);
	carLabel->setSize(200.f, 30.6524);
	carLabel->setTextSize(18);

	mGui->add(carLabel);

	tgui::Label::Ptr goatLabel = tgui::Label::create();
	goatLabel->setText("Goat: " + std::to_string(mGoatNumber));
	goatLabel->setPosition(930, 590);
	goatLabel->setSize(200.f, 30.6524);
	goatLabel->setTextSize(18);

	mGui->add(goatLabel);

	tgui::Button::Ptr runButton = tgui::Button::create();
	runButton->setText("RUN");
	runButton->setPosition(270, 620);
	runButton->setSize(170, 62.3333);
	runButton->setTextSize(30);

	mGui->add(runButton);

	runButton->connect("Clicked", &Game::RunSignal, this, repeatNumBox, choiceBox, winMessage, carLabel, goatLabel);

	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mWindow.close();
			}

			mGui->handleEvent(event); // Pass the event to the widgets
		}

		if (mClickNumber == 0)  // Remove the text when the game restarts.
		{
			winMessage->setText("");
		}

		if (mClickNumber == 2)
		{
			if (mbWin)
			{
				winMessage->setText("You won a car!\nClick any door to restart the game.");
				carLabel->setText("Car: " + std::to_string(mCarNumber));
			}
			else
			{
				winMessage->setText("You got a goat.\nClick any door to restart the game.");
				goatLabel->setText("Goat: " + std::to_string(mGoatNumber));
			}
		}

		mWindow.clear(sf::Color::White);
		mGui->draw(); // Draw all widgets
		mWindow.display();
	}
}

void Game::SignalHandler1()
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
				mDoor2->SetOpen(true);
				mDoor2->setEnabled(false);
				break;
			case 1:
				mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor3->SetOpen(true);
				mDoor3->setEnabled(false);
				break;
			}
		}
		else if (mDoor2->IsCar())
		{
			mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor3->SetOpen(true);
			mDoor3->setEnabled(false);
		}
		else if (mDoor3->IsCar())
		{
			mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor2->SetOpen(true);
			mDoor2->setEnabled(false);
		}
	}
	else if (mClickNumber == 2)
	{
		mDoor1->setEnabled(true);
		mDoor2->setEnabled(true);
		mDoor3->setEnabled(true);

		if (mDoor1->IsCar()) // You won the game in this case.
		{
			mDoor1->getRenderer()->setTexture(mCarDoorTexture);
			mDoor1->SetOpen(true);
			mbWin = true;
			mCarNumber++;
		}
		else  // You lost the game in this case.
		{
			mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor1->SetOpen(true);
			mGoatNumber++;
		}

		if (mDoor2->IsCar())
		{
			mDoor2->getRenderer()->setTexture(mCarDoorTexture);
			mDoor2->SetOpen(true);
		}
		else
		{
			mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor2->SetOpen(true);
		}

		if (mDoor3->IsCar())
		{
			mDoor3->getRenderer()->setTexture(mCarDoorTexture);
			mDoor3->SetOpen(true);
		}
		else
		{
			mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor3->SetOpen(true);
		}
	}
	else if (mClickNumber == 3)
	{
		Restart();
	}
}

void Game::SignalHandler2()
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
				mDoor1->SetOpen(true);
				break;
			case 1:
				mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor3->setEnabled(false);
				mDoor3->SetOpen(true);
				break;
			}
		}
		else if (mDoor1->IsCar())
		{
			mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor3->setEnabled(false);
			mDoor3->SetOpen(true);
		}
		else if (mDoor3->IsCar())
		{
			mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor1->setEnabled(false);
			mDoor1->SetOpen(true);
		}
	}
	else if (mClickNumber == 2)
	{
		mDoor1->setEnabled(true);
		mDoor2->setEnabled(true);
		mDoor3->setEnabled(true);

		if (mDoor1->IsCar())
		{
			mDoor1->getRenderer()->setTexture(mCarDoorTexture);
			mDoor1->SetOpen(true);
		}
		else
		{
			mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor1->SetOpen(true);
		}

		if (mDoor2->IsCar())
		{
			mDoor2->getRenderer()->setTexture(mCarDoorTexture);
			mbWin = true;
			mCarNumber++;
			mDoor2->SetOpen(true);
		}
		else  // You lost the game in this case.
		{
			mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
			mGoatNumber++;
			mDoor2->SetOpen(true);
		}

		if (mDoor3->IsCar())
		{
			mDoor3->getRenderer()->setTexture(mCarDoorTexture);
			mDoor3->SetOpen(true);
		}
		else
		{
			mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor3->SetOpen(true);
		}
	}
	else if (mClickNumber == 3)
	{
		Restart();
	}
}

void Game::SignalHandler3()
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
				mDoor1->SetOpen(true);
				break;
			case 1:
				mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor2->setEnabled(false);
				mDoor2->SetOpen(true);
				break;
			}
		}
		else if (mDoor1->IsCar())
		{
			mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor2->setEnabled(false);
			mDoor2->SetOpen(true);
		}
		else if (mDoor2->IsCar())
		{
			mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor1->setEnabled(false);
			mDoor1->SetOpen(true);
		}
	}
	else if (mClickNumber == 2)
	{
		mDoor1->setEnabled(true);
		mDoor2->setEnabled(true);
		mDoor3->setEnabled(true);

		if (mDoor1->IsCar())
		{
			mDoor1->getRenderer()->setTexture(mCarDoorTexture);
			mDoor1->SetOpen(true);
		}
		else
		{
			mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor1->SetOpen(true);
		}

		if (mDoor2->IsCar())
		{
			mDoor2->getRenderer()->setTexture(mCarDoorTexture);
			mDoor2->SetOpen(true);
		}
		else
		{
			mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor2->SetOpen(true);
		}

		if (mDoor3->IsCar())
		{
			mDoor3->getRenderer()->setTexture(mCarDoorTexture);
			mDoor3->SetOpen(true);
			mbWin = true;
			mCarNumber++;
		}
		else // You lost the game in this case.
		{
			mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
			mDoor3->SetOpen(true);
			mGoatNumber++;
		}
	}
	else if (mClickNumber == 3)
	{
		Restart();
	}
}

void Game::Restart()
{
	mClickNumber = 0;
	mDoor1->getRenderer()->setTexture(mClosedDoorTexture);
	mDoor2->getRenderer()->setTexture(mClosedDoorTexture);
	mDoor3->getRenderer()->setTexture(mClosedDoorTexture);
	mbWin = false;

	mDoor1->SetCar(false);
	mDoor2->SetCar(false);
	mDoor3->SetCar(false);

	mDoor1->SetOpen(false);
	mDoor2->SetOpen(false);
	mDoor3->SetOpen(false);

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
}

void Game::RunSignal(tgui::ComboBox::Ptr repeat, tgui::ComboBox::Ptr choice, tgui::Label::Ptr winMessage, tgui::Label::Ptr carLabel, tgui::Label::Ptr goatLabel)
{
	if (repeat->getSelectedItem() == "" || choice->getSelectedItem() == "") // If the items were not selected correctly, then do nothing.
	{
		std::cout << "Do nothing\n";
		return;
	}
	eDoorNumber doorNumber;

	int num = std::stoi(repeat->getSelectedItem().toAnsiString());  // Convert string to int

	for (int i = 0; i < num; i++)
	{
		std::cout << i << std::endl;
		// Step1: Choose one door randomly.
		int random = rand() % 3;
		switch (random)
		{
		case 0:
			doorNumber = DOOR1;
			break;
		case 1:
			doorNumber = DOOR2;
			break;
		case 2:
			doorNumber = DOOR3;
			break;
		}

		// Step2: Show one door which has a goat.
		switch (doorNumber)
		{
		case DOOR1:
			if (mDoor2->IsCar())
			{
				mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor3->SetOpen(true);
			}
			else if (mDoor3->IsCar())
			{
				mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor2->SetOpen(true);
			}
			else
			{
				mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor2->SetOpen(true);
			}
			break;
		case DOOR2:
			if (mDoor1->IsCar())
			{
				mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor3->SetOpen(true);
			}
			else if (mDoor3->IsCar())
			{
				mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor1->SetOpen(true);
			}
			else
			{
				mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor1->SetOpen(true);
			}
			break;
		case DOOR3:
			if (mDoor2->IsCar())
			{
				mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor1->SetOpen(true);
			}
			else if (mDoor1->IsCar())
			{
				mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor2->SetOpen(true);
			}
			else
			{
				mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
				mDoor2->SetOpen(true);
			}
			break;
		}

		// Step3: Make final decision depend on the choice.
		if (choice->getSelectedItem() == "Keep the choice.")
		{
			switch (doorNumber)
			{
			case DOOR1:
				if (mDoor1->IsCar()) // You won the game in this case.
				{
					mDoor1->getRenderer()->setTexture(mCarDoorTexture);
					mDoor1->SetOpen(true);
					mbWin = true;
					mCarNumber++;
				}
				else  // You lost the game in this case.
				{
					mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor1->SetOpen(true);
					mGoatNumber++;
				}

				if (mDoor2->IsCar())
				{
					mDoor2->getRenderer()->setTexture(mCarDoorTexture);
					mDoor2->SetOpen(true);
				}
				else
				{
					mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor2->SetOpen(true);
				}

				if (mDoor3->IsCar())
				{
					mDoor3->getRenderer()->setTexture(mCarDoorTexture);
					mDoor3->SetOpen(true);
				}
				else
				{
					mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor3->SetOpen(true);
				}
				break;
			case DOOR2:
				if (mDoor1->IsCar())
				{
					mDoor1->getRenderer()->setTexture(mCarDoorTexture);
					mDoor1->SetOpen(true);
				}
				else
				{
					mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor1->SetOpen(true);
				}

				if (mDoor2->IsCar()) // You won the game.
				{
					mDoor2->getRenderer()->setTexture(mCarDoorTexture);
					mDoor2->SetOpen(true);
					mbWin = true;
					mCarNumber++;
				}
				else  // You lost the game in this case.
				{
					mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor2->SetOpen(true);
					mGoatNumber++;
				}

				if (mDoor3->IsCar())
				{
					mDoor3->getRenderer()->setTexture(mCarDoorTexture);
					mDoor3->SetOpen(true);
				}
				else
				{
					mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor3->SetOpen(true);
				}
				break;
			case DOOR3:
				if (mDoor1->IsCar())
				{
					mDoor1->getRenderer()->setTexture(mCarDoorTexture);
					mDoor1->SetOpen(true);
				}
				else
				{
					mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor1->SetOpen(true);
				}

				if (mDoor2->IsCar())
				{
					mDoor2->getRenderer()->setTexture(mCarDoorTexture);
					mDoor2->SetOpen(true);
				}
				else
				{
					mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
					mDoor2->SetOpen(true);
				}

				if (mDoor3->IsCar()) // You won the game.
				{
					mDoor3->getRenderer()->setTexture(mCarDoorTexture);
					mDoor3->SetOpen(true);
					mbWin = true;
					mCarNumber++;
				}
				else // You lost the game in this case.
				{
					mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
					mGoatNumber++;
					mDoor3->SetOpen(true);
				}
				break;
			}
		}
		else if (choice->getSelectedItem() == "Change the choice.")
		{
			switch (doorNumber)
			{
			case DOOR1:
				if (mDoor2->IsOpened()) // If door2 is already opened, then open door3.
				{
					if (mDoor3->IsCar())
					{
						mDoor3->getRenderer()->setTexture(mCarDoorTexture);
						mDoor3->SetOpen(true);
						mbWin = true;
						mCarNumber++;
					}
					else
					{
						mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor3->SetOpen(true);
						mGoatNumber++;
					}
				}
				else if (mDoor3->IsOpened()) // If door3 is already opened, then open door2.
				{
					if (mDoor2->IsCar())
					{
						mDoor2->getRenderer()->setTexture(mCarDoorTexture);
						mDoor2->SetOpen(true);
						mbWin = true;
						mCarNumber++;
					}
					else
					{
						mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor2->SetOpen(true);
						mGoatNumber++;
					}
				}
				break;
			case DOOR2:
				if (mDoor1->IsOpened()) // If door1 is already opened, then open door3.
				{
					if (mDoor3->IsCar())
					{
						mDoor3->getRenderer()->setTexture(mCarDoorTexture);
						mDoor3->SetOpen(true);
						mbWin = true;
						mCarNumber++;
					}
					else
					{
						mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor3->SetOpen(true);
						mGoatNumber++;
					}
				}
				else if (mDoor3->IsOpened()) // If door3 is already opened, then open door1.
				{
					if (mDoor1->IsCar())
					{
						mDoor1->getRenderer()->setTexture(mCarDoorTexture);
						mDoor1->SetOpen(true);
						mbWin = true;
						mCarNumber++;
					}
					else
					{
						mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor1->SetOpen(true);
						mGoatNumber++;
					}
				}
				break;
			case DOOR3:
				if (mDoor2->IsOpened()) // If door2 is already opened, then open door1.
				{
					if (mDoor1->IsCar())
					{
						mDoor1->getRenderer()->setTexture(mCarDoorTexture);
						mDoor1->SetOpen(true);
						mbWin = true;
						mCarNumber++;
					}
					else
					{
						mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
						mDoor1->SetOpen(true);
						mGoatNumber++;
					}
				}
				else if (mDoor1->IsOpened()) // If door1 is already opened, then open door2.
				{
					if (mDoor2->IsCar())
					{
						mDoor2->getRenderer()->setTexture(mCarDoorTexture);
						mbWin = true;
						mCarNumber++;
						mDoor2->SetOpen(true);
					}
					else
					{
						mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
						mGoatNumber++;
						mDoor2->SetOpen(true);
					}
				}
				break;
			}
		}

		if (mbWin)
		{
			winMessage->setText("You won a car!\nClick any door to restart the game.");
			
			carLabel->setText("Car: " + std::to_string(mCarNumber) + "(" + std::to_string(static_cast<float>(mCarNumber) / static_cast<float>(mCarNumber + mGoatNumber)) + ")");
		}
		else
		{
			winMessage->setText("You got a goat.\nClick any door to restart the game.");
			goatLabel->setText("Goat: " + std::to_string(mGoatNumber) + "(" + std::to_string(static_cast<float>(mGoatNumber) / static_cast<float>(mCarNumber + mGoatNumber)) + ")");
		}

		mWindow.clear(sf::Color::White);
		mGui->draw(); // Draw all widgets
		mWindow.display();

		Restart();
	}
}
