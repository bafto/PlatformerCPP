#include "../../../include/UI/UIElements/UIText.h"
#include "../../../include/Game.h"

UIText::UIText(sf::Vector2f pos)
	:
	UIElement(sf::FloatRect(pos, { 0.f, 0.f }))
{
	drawText.setPosition(rect.getPosition());
	drawText.setFillColor(sf::Color::White);
	drawText.setCharacterSize(18);
	drawText.setString("");
}

UIText::~UIText()
{

}

void UIText::Initialize()
{
	drawText.setFont(Game::GetInstance().GetFont());
	UIElement::Initialize();
}

void UIText::render(sf::RenderTarget& target)
{
	target.draw(drawText);
	UIElement::render(target);
}
	 
void UIText::SetString(std::string str)
{
	drawText.setString(str);
}

void UIText::SetColor(sf::Color color)
{
	drawText.setFillColor(color);
}

void UIText::SetCharacterSize(unsigned int size)
{
	drawText.setCharacterSize(size);
}

std::string UIText::GetString()
{
	return drawText.getString();
}

sf::FloatRect UIText::GetBounds()
{
	return drawText.getGlobalBounds();
}