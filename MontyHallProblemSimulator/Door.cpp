#include "Door.h"

Door::Door(const sf::Texture& texture)
	: tgui::Picture(texture)
	, mbIsCar(false)
{
}

Door::~Door()
{
}

bool Door::IsCar()
{
	return mbIsCar;
}

void Door::SetCar(bool car)
{
	mbIsCar = car;
}
