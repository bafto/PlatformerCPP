#include "../../../include/UI/UIStates/TestState.h"
#include "../../../include/Game.h"

TestState::TestState()
	:
	UIState(),
	panel(sf::FloatRect(200.f, 200.f, 400.f, 400.f)),
	btn(sf::FloatRect(50.f, 50.f, 100.f, 40.f))
{
	panel.SetColor(sf::Color::Blue);
	
	btn.SetColor(sf::Color(128, 128, 128));
	btn.SetHoverColor(sf::Color::White);
	btn.SetClickColor(sf::Color::Black);
	btn.SetTextColor(sf::Color::White);
	btn.SetString("Click me!");

	panel.Append(&btn);
	Append(&panel);
}

TestState::~TestState()
{

}