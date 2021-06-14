#include "../../../include/UI/UIElements/UIButton.h"

UIButton::UIButton(sf::FloatRect bounds)
	:
	UIPanel(bounds),
	text(sf::Vector2f(bounds.left, bounds.top)),
	hoverSound(nullptr),
	clickSound(nullptr),
	releaseSound(nullptr)
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

	sf::Vector2f textSize = text.GetSize();
	text.SetRelativePosition((GetSize() / 2.f) - sf::Vector2f(textSize.x / 2.f, textSize.y / 2.f));

	OnMouseEnter += [&](UIElement*) { rect.setOutlineThickness(1); };
	OnMouseEnter += [&](UIElement*) { if (hoverSound)hoverSound->play(); };
	OnClick += [&](UIElement*) { rect.setOutlineColor(clickColor); };
	OnClick += [&](UIElement*) { if (clickSound)clickSound->play(); };
	OnHold += [&](UIElement*) { rect.setOutlineThickness(0); };
	OnRelease += [&](UIElement*) { rect.setOutlineColor(hoverColor); };
	OnRelease += [&](UIElement*) { if (releaseSound)releaseSound->play(); };
	OnHover += [&](UIElement*) { rect.setOutlineColor(hoverColor); rect.setOutlineThickness(1); };
	OnMouseExit += [&](UIElement*) { rect.setOutlineThickness(0); };
}

void UIButton::SetString(std::string str)
{
	text.SetString(str);
	sf::Vector2f textSize = text.GetSize();
	text.SetRelativePosition((GetSize() / 2.f) - sf::Vector2f(textSize.x / 2.f, textSize.y / 2.f));
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

void UIButton::SetHoverSound(sf::Sound* sound)
{
	hoverSound = sound;
}

void UIButton::SetClickSound(sf::Sound* sound)
{
	clickSound = sound;
}

void UIButton::SetReleaseSound(sf::Sound* sound)
{
	releaseSound = sound;
}