#include "../../../include/UI/UIElements/UIButton.h"

UIButton::UIButton(sf::FloatRect bounds)
	:
	UIPanel(bounds),
	text(sf::Vector2f(bounds.left, bounds.top))
{
	Append(&text);
}

UIButton::~UIButton()
{

}

void UIButton::Initialize()
{
	UIPanel::Initialize();
	text.Initialize();

	rect.setFillColor(sf::Color::Black);
	rect.setOutlineThickness(0);

	text.SetColor(sf::Color::White);
	text.SetCharacterSize(18);

	sf::FloatRect textRect = text.GetLocalBounds();
	text.SetRelativePosition(rect.getSize() / 2.f - sf::Vector2f(textRect.width / 2.f, textRect.height / 2.f));

	OnMouseEnter += [&](UIElement*) { rect.setOutlineThickness(1); };
	OnClick += [&](UIElement*) { rect.setOutlineColor(clickColor); };
	OnHold += [&](UIElement*) { rect.setOutlineColor(clickColor); };
	OnRelease += [&](UIElement*) { rect.setOutlineColor(hoverColor); };
	OnHover += [&](UIElement*) { rect.setOutlineColor(hoverColor); };
	OnMouseExit += [&](UIElement*) { rect.setOutlineThickness(0); };
}

void UIButton::SetString(std::string str)
{
	text.SetString(str);
	sf::FloatRect textRect = text.GetLocalBounds();
	text.SetRelativePosition((rect.getSize() / 2.f) - sf::Vector2f(textRect.width / 2.f, textRect.height / 2.f));
}

void UIButton::SetTextColor(sf::Color color)
{
	text.SetColor(color);
}

void UIButton::SetColor(sf::Color color)
{
	UIPanel::SetColor(color);
}

void UIButton::SetHoverColor(sf::Color color)
{
	hoverColor = color;
}

void UIButton::SetClickColor(sf::Color color)
{
	clickColor = color;
}

void UIButton::SetCharacterSize(unsigned int size)
{
	text.SetCharacterSize(size);
}