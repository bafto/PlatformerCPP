#include "../../../include/UI/UIElements/UIText.h"
#include "../../../include/Game.h"

UIText::UIText(sf::Vector2f pos)
	:
	UIElement(sf::FloatRect(pos, { 0.f, 0.f }))
{
}

UIText::~UIText()
{

}

void UIText::Initialize()
{
	drawText.setPosition(rect.getPosition());
	drawText.setFillColor(sf::Color::White);
	drawText.setCharacterSize(18);
	drawText.setString("");
	drawText.setFont(Game::GetInstance().GetFont());
	UIElement::Initialize();
}

void UIText::render(sf::RenderTarget& target)
{
	target.draw(drawText);
	UIElement::render(target);
}

void UIText::SetAbsolutePosition(sf::Vector2f pos)
{
	UIElement::SetAbsolutePosition(pos);
	drawText.setPosition(pos);
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

sf::Vector2f UIText::GetSize()
{
	sf::FloatRect bounds = drawText.getLocalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}