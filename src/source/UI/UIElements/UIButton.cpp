#include "../../../include/UI/UIElements/UIButton.h"

UIButton::UIButton(sf::FloatRect bounds)
	:
	UIElement(bounds)
{
	rect.setFillColor(sf::Color::Red);
}

UIButton::~UIButton()
{

}