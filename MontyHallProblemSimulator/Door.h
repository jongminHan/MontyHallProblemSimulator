#pragma once
#include <TGUI/TGUI.hpp>

class Door : public tgui::Picture
{
public:
	Door(const sf::Texture& texture);
	virtual ~Door();
	bool IsCar();
	bool IsOpened();
	void SetCar(bool car);
	void SetOpen(bool door);
private:
	bool mbIsCar; // True for car. False for goat. Default value is false.
	bool mbIsOpened;
};