#include "Door.h"

Door::Door(const sf::Texture& texture)
	: tgui::Picture(texture)
	, mbIsCar(false)
	, mbIsOpened(false)
{
}

Door::~Door()
{
}

bool Door::IsCar()
{
	return mbIsCar;
}

bool Door::IsOpened()
{
	return mbIsOpened;
}

void Door::SetCar(bool car)
{
	mbIsCar = car;
}

void Door::SetOpen(bool door)
{
	mbIsOpened = door;
}
