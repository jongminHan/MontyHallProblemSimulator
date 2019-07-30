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
	tgui::Gui gui{ mWindow };  // Create the gui and attach it to the window

	gui.add(mDoor1);
	gui.add(mDoor2);
	gui.add(mDoor3);

	mDoor1->connect("Clicked", &Game::SignalHandler1, this);
	mDoor2->connect("Clicked", &Game::SignalHandler2, this);
	mDoor3->connect("Clicked", &Game::SignalHandler3, this);

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

	tgui::Label::Ptr winMessage = tgui::Label::create();
	winMessage->setText("");
	winMessage->setSize(387.2, 46.5575);
	winMessage->setPosition(250, 40);
	winMessage->setTextSize(18);

	gui.add(winMessage);


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

	gui.add(repeatNumBox);
	gui.add(choiceBox);

	tgui::Label::Ptr carLabel = tgui::Label::create();
	carLabel->setText("Car: " + std::to_string(mCarNumber));
	carLabel->setPosition(930, 560);
	carLabel->setSize(137.2, 30.6524);
	carLabel->setTextSize(18);

	gui.add(carLabel);

	tgui::Label::Ptr goatLabel = tgui::Label::create();
	goatLabel->setText("Goat: " + std::to_string(mGoatNumber));
	goatLabel->setPosition(930, 590);
	goatLabel->setSize(137.2, 30.6524);
	goatLabel->setTextSize(18);

	gui.add(goatLabel);

	tgui::Button::Ptr runButton = tgui::Button::create();
	runButton->setText("RUN");
	runButton->setPosition(270, 620);
	runButton->setSize(170, 62.3333);
	runButton->setTextSize(30);

	gui.add(runButton);

	runButton->connect("Clicked", &Game::RunSignal, this, repeatNumBox, choiceBox);

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
		gui.draw(); // Draw all widgets
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
	else if (mClickNumber == 2)
	{
		mDoor1->setEnabled(true);
		mDoor2->setEnabled(true);
		mDoor3->setEnabled(true);

		if (mDoor1->IsCar()) // You won the game in this case.
		{
			mDoor1->getRenderer()->setTexture(mCarDoorTexture);
			mbWin = true;
			mCarNumber++;
		}
		else  // You lost the game in this case.
		{
			mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
			mGoatNumber++;
		}

		if (mDoor2->IsCar())
		{
			mDoor2->getRenderer()->setTexture(mCarDoorTexture);
		}
		else
		{
			mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
		}

		if (mDoor3->IsCar())
		{
			mDoor3->getRenderer()->setTexture(mCarDoorTexture);
		}
		else
		{
			mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
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
	else if (mClickNumber == 2)
	{
		mDoor1->setEnabled(true);
		mDoor2->setEnabled(true);
		mDoor3->setEnabled(true);

		if (mDoor1->IsCar())
		{
			mDoor1->getRenderer()->setTexture(mCarDoorTexture);
		}
		else
		{
			mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
		}

		if (mDoor2->IsCar())
		{
			mDoor2->getRenderer()->setTexture(mCarDoorTexture);
			mbWin = true;
			mCarNumber++;
		}
		else  // You lost the game in this case.
		{
			mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
			mGoatNumber++;
		}

		if (mDoor3->IsCar())
		{
			mDoor3->getRenderer()->setTexture(mCarDoorTexture);
		}
		else
		{
			mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
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
	else if (mClickNumber == 2)
	{
		mDoor1->setEnabled(true);
		mDoor2->setEnabled(true);
		mDoor3->setEnabled(true);

		if (mDoor1->IsCar())
		{
			mDoor1->getRenderer()->setTexture(mCarDoorTexture);
		}
		else
		{
			mDoor1->getRenderer()->setTexture(mGoatDoorTexture);
		}

		if (mDoor2->IsCar())
		{
			mDoor2->getRenderer()->setTexture(mCarDoorTexture);
		}
		else
		{
			mDoor2->getRenderer()->setTexture(mGoatDoorTexture);
		}

		if (mDoor3->IsCar())
		{
			mDoor3->getRenderer()->setTexture(mCarDoorTexture);
			mbWin = true;
			mCarNumber++;
		}
		else // You lost the game in this case.
		{
			mDoor3->getRenderer()->setTexture(mGoatDoorTexture);
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

void Game::RunSignal(tgui::ComboBox::Ptr repeat, tgui::ComboBox::Ptr choice)
{
	if (repeat->getSelectedItem() == "" || choice->getSelectedItem() == "") // If the items were not selected correctly, then do nothing.
	{
		std::cout << "Do nothing\n";
		return;
	}

	int num = std::stoi(repeat->getSelectedItem().toAnsiString());  // Convert string to int

	for (int i = 0; i < num; i++)
	{
		// Step1: Choose one door randomly.
		int random = rand() % 3;
		switch (random)
		{
		case 0:
			SignalHandler1();
			break;
		case 1:
			SignalHandler2();
			break;
		case 2:
			SignalHandler3();
			break;
		}

		// Step2: Show one door which has a goat.
		// Step3: Make final decision depent on the choice.
	}
	
}
