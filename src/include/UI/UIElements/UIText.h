#pragma once

#include "../UIElement.h"

class UIText : public UIElement
{
public:
	UIText(sf::Vector2f pos);
	virtual ~UIText();

	virtual void Initialize() override;

	virtual void render(sf::RenderTarget& target);

	virtual void SetAbsolutePosition(sf::Vector2f pos) override;

	void SetString(std::string str);
	void SetColor(sf::Color color);
	void SetCharacterSize(unsigned int size);

	std::string GetString();
	virtual sf::Vector2f GetSize() override;

private:
	sf::Text drawText;
};