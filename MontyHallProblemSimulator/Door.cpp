#include "Door.h"

Door::Door(const sf::Texture& texture)
	: tgui::Picture(texture)
	, mClickState(CLICKABLE)
{
}

Door::~Door()
{
}
