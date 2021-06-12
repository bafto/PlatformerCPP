#include "../../../include/UI/UIStates/TestState.h"
#include "../../../include/Game.h"

TestState::TestState()
	:
	UIState(),
	btn(sf::FloatRect(100.f, 100.f, 100.f, 40.f))
{
	btn.OnClick += [&](UIElement*) { Game::GetInstance().gameMode = Game::GameMode::InGame; };
	Append(&btn);
}

TestState::~TestState()
{

}