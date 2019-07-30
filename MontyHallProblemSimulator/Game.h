#pragma once
#include <iostream>
#include "Door.h"
#include "eDoorNumber.h"

class Game
{
public:
	Game();
	virtual ~Game();
	bool Init();
	void Run();
	void SignalHandler1();
	void SignalHandler2();
	void SignalHandler3();
	void Restart();
	void RunSignal(tgui::ComboBox::Ptr repeat, tgui::ComboBox::Ptr choice, tgui::Label::Ptr winMessage, tgui::Label::Ptr carLabel, tgui::Label::Ptr goatLabel);
private:
	sf::RenderWindow mWindow;
	sf::Texture mClosedDoorTexture;
	sf::Texture mGoatDoorTexture;
	sf::Texture mCarDoorTexture;
	std::shared_ptr<Door> mDoor1;
	std::shared_ptr<Door> mDoor2;
	std::shared_ptr<Door> mDoor3;
	int mClickNumber;
	int mCarNumber;
	int mGoatNumber;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	bool mbWin;
};