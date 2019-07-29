#pragma once
#include <TGUI/TGUI.hpp>

class Door : public tgui::Picture
{
public:
	Door(const sf::Texture& texture);
	virtual ~Door();
	bool IsCar();
	void SetCar(bool car);
private:
	bool mbIsCar; // True for car. False for goat. Default value is false.
};