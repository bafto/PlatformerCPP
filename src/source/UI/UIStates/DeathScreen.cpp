#include "../../../include/UI/UIStates/DeathScreen.h"
#include "../../../include/Game.h"
#include "../../../include/GameException.h"

DeathScreen::DeathScreen()
	:
	UIState(),
	MainPanel({ 0.f, 0.f, (float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height }),
	Headline({ 0.f, 0.f }),
	Retry(UIButton::StandardBounds()),
	MainMenu(UIButton::StandardBounds()),
	Quit(UIButton::StandardBounds())
{
	if (!btnHoverBuffer.loadFromFile("assets\\sounds\\buttonHover.wav"))
		throw FILEEXCEPTION(std::string("assets\\sounds\\buttonHover.wav"));
	btnHover.setBuffer(btnHoverBuffer);
	if (!btnClickBuffer.loadFromFile("assets\\sounds\\buttonClick.wav"))
		throw FILEEXCEPTION(std::string("assets\\sounds\\buttonClick.wav"));
	btnClick.setBuffer(btnClickBuffer);

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
	Retry.SetHoverSound(&btnHover);
	Retry.SetClickSound(&btnClick);

	MainMenu.SetPercentagePositionCentered({ 50, 38 });
	MainMenu.SetString("Main Menu");
	MainMenu.SetTextColor(sf::Color::White);
	MainMenu.SetHoverColor(sf::Color::White);
	MainMenu.SetColor(sf::Color(128, 128, 128));
	MainMenu.OnRelease += [&](UIElement*) {Game::GetInstance().gameMode = Game::GameMode::MainMenu; };
	MainMenu.SetHoverSound(&btnHover);
	MainMenu.SetClickSound(&btnClick);

	Quit.SetPercentagePositionCentered({ 50, 46 });
	Quit.SetString("Rage Quit");
	Quit.SetTextColor(sf::Color::White);
	Quit.SetHoverColor(sf::Color::White);
	Quit.SetColor(sf::Color(128, 128, 128));
	Quit.OnRelease += [&](UIElement*) {Game::GetInstance().wnd.close(); };
	Quit.SetHoverSound(&btnHover);
	Quit.SetClickSound(&btnClick);

}