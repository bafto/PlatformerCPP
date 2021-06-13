#include "../../../include/UI/UIStates/TestState.h"
#include "../../../include/Game.h"
#include "../../../include/Debug.h"

TestState::TestState()
	:
	UIState(),
	panel(sf::FloatRect(200.f, 200.f, 400.f, 400.f)),
	btn(sf::FloatRect(0.f, 0.f, 100.f, 40.f))
{
	panel.Append(&btn);
	Append(&panel);
}

TestState::~TestState()
{

}

void TestState::Initialize()
{
	UIState::Initialize();

	panel.SetColor(sf::Color::Blue);

	btn.SetColor(sf::Color(128, 128, 128));
	btn.SetHoverColor(sf::Color::White);
	btn.SetClickColor(sf::Color::Black);
	btn.SetTextColor(sf::Color::White);
	btn.SetString("Click me!");
	btn.SetPercentagePositionCentered(sf::Vector2f(50, 50));

	btn.OnClick += [&](UIElement*) {Debug::Println("clicked"); };
	btn.OnRelease += [&](UIElement*) {Debug::Println("released"); };
}