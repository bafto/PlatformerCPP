#pragma once

#include "../UIElement.h"

class UIButton : public UIElement
{
public:
	UIButton(sf::FloatRect bounds);
	virtual ~UIButton();
};