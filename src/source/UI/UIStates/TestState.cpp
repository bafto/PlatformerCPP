#include "../../../include/UI/UIStates/TestState.h"
#include "../../../include/Game.h"

TestState::TestState()
	:
	UIState(),
	btn(sf::FloatRect(100.f, 100.f, 100.f, 40.f)),
	text(sf::Vector2f(100.f, 100.f))
{
	btn.OnClick += [&](UIElement*) { Game::GetInstance().gameMode = Game::GameMode::InGame; };
	btn.SetColor(sf::Color::Blue);
	Append(&btn);

	text.SetString("Hello World");
	Append(&text);
}

TestState::~TestState()
{

}