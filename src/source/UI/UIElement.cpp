#include "../../include/UI/UIElement.h"
#include "../../include/Game.h"
#include "../../include/Utility.h"

UIElement::UIElement()
	:
	parent(nullptr)
{
	rect.setPosition(0.f, 0.f);
	rect.setSize(sf::Vector2f(0.f, 0.f));
	rect.setFillColor(sf::Color::Transparent);
}

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

void UIElement::Initialize()
{
	Recalculate();
	for (auto& c : children)
		c->Initialize();
}

void UIElement::update(const float& DeltaTime)
{
	for (auto& c : children)
		c->update(DeltaTime);
	if (util::ShapeVecIntersect(rect, sf::Vector2f(Game::GetInstance().input.MousePosWindow())))
	{
		if (!mouseHovered)
			OnMouseEnter(this);
		else if (mouseHovered)
			OnHover(this);
		if (Game::GetInstance().input.MouseState(sf::Mouse::Left).pressed)
			OnClick(this);
		else if (Game::GetInstance().input.MouseState(sf::Mouse::Left).released)
			OnRelease(this);
		else if (Game::GetInstance().input.MouseState(sf::Mouse::Left).held)
			OnHold(this);

		mouseHovered = true;
	}
	else
	{
		if (mouseHovered)
			OnMouseExit(this);

		mouseHovered = false;
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
	element->Recalculate();
}

void UIElement::Remove(UIElement* element)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i] == element)
		{
			element->parent = nullptr;
			element->Recalculate();
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
		children[index]->Recalculate();
		children.erase(children.begin() + index);
	}
}

void UIElement::Recalculate()
{
	SetRelativePosition(GetRelativePosition());
	for (auto& c : children)
		c->Recalculate();
}

void UIElement::SetRelativePosition(sf::Vector2f pos)
{
	if (parent != nullptr)
		rect.setPosition(parent->rect.getPosition() + pos);
	else
		SetAbsolutePosition(pos);
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