#pragma once
#include <TGUI/TGUI.hpp>

class Door : public tgui::Picture
{
public:
	Door(const sf::Texture& texture);
	virtual ~Door();
};