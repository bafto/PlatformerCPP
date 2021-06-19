#pragma once

#include "UIElement.h"

//Base class for all UIStates
class UIState : public NonCopyable //NonCopyable because of the UIElement pointers
{
public:
	UIState();
	virtual ~UIState();

	virtual void Initialize();

	virtual void update(const float& DeltaTime);
	virtual void render(sf::RenderTarget& target);

	//Append/remove UIElements to/from elements
	void Append(UIElement* element);
	void Remove(UIElement* element);
	void Remove(size_t index);

protected:
	std::vector<UIElement*> elements; //The UIElements that are updated

};