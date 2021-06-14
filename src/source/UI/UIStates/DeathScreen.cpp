#include "../../../include/UI/UIStates/DeathScreen.h"
#include "../../../include/Game.h"

DeathScreen::DeathScreen()
	:
	UIState(),
	MainPanel({ 0.f, 0.f, (float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height }),
	Headline({ 0.f, 0.f }),
	Retry(UIButton::StandardBounds()),
	MainMenu(UIButton::StandardBounds()),
	Quit(UIButton::StandardBounds())
{
	MainPanel.Append(&Headline);
	MainPanel.Append(&Retry);
	MainPanel.Append(&MainMenu);
	MainPanel.Append(&Quit);
	Append(&MainPanel);
}

DeathScreen::~DeathScreen()
{

}

void DeathScreen::Initialize()
{
	UIState::Initialize();

	MainPanel.SetColor(sf::Color(211, 211, 211));

	Headline.SetString("You Died (dipshit)");
	Headline.SetCharacterSize(35);
	Headline.SetColor(sf::Color::White);
	Headline.SetPercentagePositionCentered({ 50, 15 });

	Retry.SetPercentagePositionCentered({ 50, 30 });
	Retry.SetString("Retry");
	Retry.SetTextColor(sf::Color::White);
	Retry.SetHoverColor(sf::Color::White);
	Retry.SetColor(sf::Color(128, 128, 128));
	Retry.OnRelease += [&](UIElement*) { Game::GetInstance().Reset(Game::GetInstance().level.GetFilePath()); };

	MainMenu.SetPercentagePositionCentered({ 50, 38 });
	MainMenu.SetString("Main Menu");
	MainMenu.SetTextColor(sf::Color::White);
	MainMenu.SetHoverColor(sf::Color::White);
	MainMenu.SetColor(sf::Color(128, 128, 128));
	MainMenu.OnRelease += [&](UIElement*) {Game::GetInstance().gameMode = Game::GameMode::MainMenu; };

	Quit.SetPercentagePositionCentered({ 50, 46 });
	Quit.SetString("Quit");
	Quit.SetTextColor(sf::Color::White);
	Quit.SetHoverColor(sf::Color::White);
	Quit.SetColor(sf::Color(128, 128, 128));
	Quit.OnRelease += [&](UIElement*) {Game::GetInstance().wnd.close(); };

}