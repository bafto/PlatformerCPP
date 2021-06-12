#include "../../include/UI/UIElement.h"
#include "../../include/Game.h"
#include "../../include/Utility.h"

UIElement::UIElement(sf::FloatRect bounds, UIElement* parent)
	:
	parent(parent)
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