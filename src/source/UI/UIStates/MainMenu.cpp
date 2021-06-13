#include "../../../include/UI/UIStates/MainMenu.h"
#include "../../../include/Game.h"

MainMenu::MainMenu()
	:
	UIState(),
	HomeScreen({ 0.f, 0.f, (float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height }),
	Headline({ 0.f, 0.f }),
	NewGame({ 0.f, 0.f, 100.f, 50.f }),
	LoadLevel({ 0.f, 0.f, 100.f, 50.f }),
	Quit({ 0.f, 0.f, 100.f, 50.f })
{
	HomeScreen.Append(&Headline);
	HomeScreen.Append(&NewGame);
	HomeScreen.Append(&LoadLevel);
	HomeScreen.Append(&Quit);
	Append(&HomeScreen);
}

MainMenu::~MainMenu()
{

}

void MainMenu::Initialize()
{
	UIState::Initialize();

	HomeScreen.SetColor(sf::Color(211, 211, 211));

	Headline.SetString("PlatformerCPP");
	Headline.SetCharacterSize(35);
	Headline.SetColor(sf::Color::Black);
	Headline.SetPercentagePositionCentered({ 50, 15 });

	NewGame.SetPercentagePositionCentered({ 50, 30 });
	NewGame.SetString("New Game");
	NewGame.SetTextColor(sf::Color::White);
	NewGame.SetColor(sf::Color(128, 128, 128));
	NewGame.OnRelease += [&](UIElement*) {Game::GetInstance().gameMode = Game::GameMode::InGame; };

	LoadLevel.SetPercentagePositionCentered({ 50, 38 });
	LoadLevel.SetString("Load Level");
	LoadLevel.SetTextColor(sf::Color::White);
	LoadLevel.SetColor(sf::Color(128, 128, 128));
	
	Quit.SetPercentagePositionCentered({ 50, 46 });
	Quit.SetString("Quit");
	Quit.SetTextColor(sf::Color::White);
	Quit.SetColor(sf::Color(128, 128, 128));
	Quit.OnRelease += [&](UIElement*) {Game::GetInstance().wnd.close(); };
}