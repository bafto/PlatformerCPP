#pragma once

#include "../UIElement.h"

class UIPanel : public UIElement
{
public:
	UIPanel(sf::FloatRect bounds);
	virtual ~UIPanel();

	virtual void SetColor(sf::Color color);
};