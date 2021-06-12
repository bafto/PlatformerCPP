#pragma once

#include "../UIElement.h"

class UIText : public UIElement
{
public:
	UIText(sf::Vector2f pos);
	virtual ~UIText();

	virtual void Initialize() override;

	virtual void render(sf::RenderTarget& target);

	void SetString(std::string str);
	void SetColor(sf::Color color);
	void SetCharacterSize(unsigned int size);

	std::string GetString();
	sf::FloatRect GetBounds();
	
private:
	sf::Text drawText;
};