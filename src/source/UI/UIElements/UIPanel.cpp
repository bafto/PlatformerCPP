#include "../../../include/UI/UIElements/UIPanel.h"

UIPanel::UIPanel(sf::FloatRect bounds)
	:
	UIElement(bounds)
{
	rect.setFillColor(sf::Color::White);
}

UIPanel::~UIPanel()
{

}

void UIPanel::SetColor(sf::Color color)
{
	rect.setFillColor(color);
}