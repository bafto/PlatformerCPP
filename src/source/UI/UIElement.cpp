#include "../../include/UI/UIElement.h"
#include "../../include/Game.h"
#include "../../include/Utility.h"

UIElement::UIElement(sf::FloatRect bounds)
	:
	parent(nullptr)
{
	rect.setPosition(bounds.left, bounds.top);
	rect.setSize(sf::Vector2f(bounds.width, bounds.height));
	rect.setFillColor(sf::Color::Transparent);
}

UIElement::~UIElement()
{

}

void UIElement::update(const float& DeltaTime)
{
	for (auto& c : children)
		c->update(DeltaTime);
	if (util::ShapeVecIntersect(rect, sf::Vector2f(Game::GetInstance().input.MousePosWindow())))
	{
		OnHover(this);
		if (Game::GetInstance().input.MouseState(sf::Mouse::Left).pressed)
			OnClick(this);
		else if (Game::GetInstance().input.MouseState(sf::Mouse::Left).released)
			OnRelease(this);
		else if (Game::GetInstance().input.MouseState(sf::Mouse::Left).held)
			OnHold(this);
	}
}

void UIElement::render(sf::RenderTarget& target)
{
	target.draw(rect);
	for (auto& c : children)
		c->render(target);
}

void UIElement::Append(UIElement* element)
{
	children.push_back(element);
	element->parent = this;
	element->SetRelativePosition(element->GetRelativePosition());
}

void UIElement::Remove(UIElement* element)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i] == element)
		{
			element->parent = nullptr;
			children.erase(children.begin() + i);
			break;
		}
	}
}

void UIElement::Remove(size_t index)
{
	if (index < children.size())
	{
		children[index]->parent = nullptr;
		children.erase(children.begin() + index);
	}
}

void UIElement::SetRelativePosition(sf::Vector2f pos)
{
	rect.setPosition(parent->rect.getPosition() + pos);
}

void UIElement::SetAbsolutePosition(sf::Vector2f pos)
{
	rect.setPosition(pos);
}

sf::Vector2f UIElement::GetRelativePosition()
{
	if (parent != nullptr)
		return rect.getPosition() - parent->GetAbsolutePosition();
	return GetAbsolutePosition();
}

sf::Vector2f UIElement::GetAbsolutePosition()
{
	return rect.getPosition();
}