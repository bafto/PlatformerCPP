#pragma once

#include "../GeneralIncludes.h"
#include "../Delegate.h"

class UIElement
{
private:
	friend class UIState;
public:
	UIElement();
	UIElement(sf::FloatRect bounds);
	virtual ~UIElement();

	virtual void update(const float& DeltaTime);
	virtual void render(sf::RenderTarget& target);

	void Append(UIElement* element);
	void Remove(UIElement* element);
	void Remove(size_t index);

	void SetRelativePosition(sf::Vector2f pos);
	void SetAbsolutePosition(sf::Vector2f pos);

	sf::Vector2f GetRelativePosition();
	sf::Vector2f GetAbsolutePosition();

	void Recalculate();

protected:
	sf::RectangleShape rect;
	std::vector<UIElement*> children;
	UIElement* parent;

public:
	Delegate<void(UIElement* element)> OnMouseEnter;
	Delegate<void(UIElement* element)> OnMouseExit;
	Delegate<void(UIElement* element)> OnHover;
	Delegate<void(UIElement* element)> OnClick;
	Delegate<void(UIElement* element)> OnRelease;
	Delegate<void(UIElement* element)> OnHold;

private:
	bool mouseHovered = false;
};