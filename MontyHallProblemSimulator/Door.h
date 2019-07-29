#pragma once
#include <TGUI/TGUI.hpp>
#include "eClick.h"

class Door : public tgui::Picture
{
public:
	Door(const sf::Texture& texture);
	virtual ~Door();
	void ClickSignal();
	eClick GetClickState();
	void SetClickState(eClick state);
private:
	eClick mClickState;
};