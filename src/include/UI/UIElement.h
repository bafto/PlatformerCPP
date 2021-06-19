#pragma once

#include "../GeneralIncludes.h"
#include "../Delegate.h"
#include "../NonCopyable.h"

//Base class for all UIElements
class UIElement : public NonCopyable //NonCopyable because of the UIElement pointers
{
private:
	friend class UIState;
public:
	UIElement();
	UIElement(sf::FloatRect bounds);
	virtual ~UIElement();

	virtual void Initialize();

	virtual void update(const float& DeltaTime);
	virtual void render(sf::RenderTarget& target);

	void Append(UIElement* element);
	void Remove(UIElement* element);
	void Remove(size_t index);

	virtual void SetRelativePosition(sf::Vector2f pos);
	virtual void SetAbsolutePosition(sf::Vector2f pos);
	virtual void SetPercentagePosition(sf::Vector2f pos);
	virtual void SetPercentagePositionCentered(sf::Vector2f pos);

	virtual sf::Vector2f GetRelativePosition();
	virtual sf::Vector2f GetAbsolutePosition();
	virtual sf::Vector2f GetSize();

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
	sf::Vector2f relativePosition;
	bool mouseHovered = false;
};