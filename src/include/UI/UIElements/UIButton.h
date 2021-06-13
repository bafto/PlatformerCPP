#pragma once

#include "../UIElements/UIPanel.h"
#include "../UIElements/UIText.h"

class UIButton : public UIPanel
{
public:
	UIButton(sf::FloatRect bounds);
	virtual ~UIButton();

	virtual void Initialize() override;

	void SetString(std::string str);
	void SetTextColor(sf::Color color);
	void SetColor(sf::Color color);
	void SetHoverColor(sf::Color color);
	void SetClickColor(sf::Color color);
	void SetCharacterSize(unsigned int size);

private:
	UIText text;
	sf::Color hoverColor, clickColor;

};