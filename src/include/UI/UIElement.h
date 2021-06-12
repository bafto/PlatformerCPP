#pragma once

#include "../GeneralIncludes.h"
#include "../Delegate.h"

class UIElement
{
public:
	UIElement(sf::FloatRect bounds, UIElement* parent);
	virtual ~UIElement();

	virtual void update(const float& DeltaTime);
	virtual void render(sf::RenderTarget& target);

protected:
	std::vector<UIElement*> children;
	UIElement* parent;
public:
	sf::RectangleShape rect;

	Delegate<void(UIElement* element)> OnHover;
	Delegate<void(UIElement* element)> OnClick;
	Delegate<void(UIElement* element)> OnRelease;
	Delegate<void(UIElement* element)> OnHold;
};