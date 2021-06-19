#include "../../include/UI/UIState.h"
#include "../../include/Game.h"

UIState::UIState()
{

}

UIState::~UIState()
{

}

void UIState::Initialize()
{
	for (auto& e : elements)
		e->Initialize();
}

void UIState::update(const float& DeltaTime)
{
	for (auto& e : elements)
		e->update(DeltaTime);
}

void UIState::render(sf::RenderTarget& target)
{
	//render all elements in HUD view
	target.setView(Game::GetInstance().GetHUDView());

	for (auto& e : elements)
		e->render(target);

	target.setView(Game::GetInstance().GetGameView());
}

void UIState::Append(UIElement* element)
{
	element->parent = nullptr;
	element->Recalculate();
	elements.push_back(element);
}

void UIState::Remove(UIElement* element)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		if (elements[i] == element)
		{
			elements.erase(elements.begin() + i);
			break;
		}
	}
}

void UIState::Remove(size_t index)
{
	if (index < elements.size())
		elements.erase(elements.begin() + index);
}