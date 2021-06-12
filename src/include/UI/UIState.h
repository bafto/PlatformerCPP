#pragma once

#include "UIElement.h"

class UIState : public NonCopyable
{
public:
	UIState();
	virtual ~UIState();

	virtual void Initialize();

	virtual void update(const float& DeltaTime);
	virtual void render(sf::RenderTarget& target);

	void Append(UIElement* element);
	void Remove(UIElement* element);
	void Remove(size_t index);

private:
	std::vector<UIElement*> elements;

};