#include "../../../include/UI/UIStates/MainMenu.h"
#include "../../../include/Game.h"

MainMenu::MainMenu()
	:
	UIState(),
	HomeScreen({ 0.f, 0.f, (float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height }),
	Headline({ 0.f, 0.f }),
	NewGame(UIButton::StandardBounds()),
	LoadLevel(UIButton::StandardBounds()),
	Quit(UIButton::StandardBounds()),
	ChooseDifficulty({ 0.f, 0.f, (float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height }),
	Headline2({ 0.f, 0.f }),
	Difficulty1(UIButton::StandardBounds()),
	Difficulty2(UIButton::StandardBounds()),
	Difficulty3(UIButton::StandardBounds()),
	Back(UIButton::StandardBounds())
{
	HomeScreen.Append(&Headline);
	HomeScreen.Append(&NewGame);
	HomeScreen.Append(&LoadLevel);
	HomeScreen.Append(&Quit);
	Append(&HomeScreen);

	ChooseDifficulty.Append(&Headline2);
	ChooseDifficulty.Append(&Difficulty1);
	ChooseDifficulty.Append(&Difficulty2);
	ChooseDifficulty.Append(&Difficulty3);
	ChooseDifficulty.Append(&Back);
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
	NewGame.OnRelease += [&](UIElement*) { elements[0] = &ChooseDifficulty; };

	LoadLevel.SetPercentagePositionCentered({ 50, 38 });
	LoadLevel.SetString("Load Level");
	LoadLevel.SetTextColor(sf::Color::White);
	LoadLevel.SetColor(sf::Color(128, 128, 128));
	
	Quit.SetPercentagePositionCentered({ 50, 46 });
	Quit.SetString("Quit");
	Quit.SetTextColor(sf::Color::White);
	Quit.SetColor(sf::Color(128, 128, 128));
	Quit.OnRelease += [&](UIElement*) {Game::GetInstance().wnd.close(); };

	ChooseDifficulty.Initialize();
	ChooseDifficulty.SetColor(sf::Color(211, 211, 211));

	Headline2.SetString("PlatformerCPP");
	Headline2.SetCharacterSize(35);
	Headline2.SetColor(sf::Color::Black);
	Headline2.SetPercentagePositionCentered({ 50, 15 });

	Difficulty1.SetPercentagePositionCentered({ 50, 30 });
	Difficulty1.SetString("Easy");
	Difficulty1.SetTextColor(sf::Color::White);
	Difficulty1.SetColor(sf::Color(128, 128, 128));
	Difficulty1.OnRelease += [&](UIElement*) {Game::GetInstance().Difficulty = 1; Game::GetInstance().Reset("assets\\Levels\\level0.level"); };

	Difficulty2.SetPercentagePositionCentered({ 50, 38 });
	Difficulty2.SetString("Medium");
	Difficulty2.SetTextColor(sf::Color::White);
	Difficulty2.SetColor(sf::Color(128, 128, 128));
	Difficulty2.OnRelease += [&](UIElement*) {Game::GetInstance().Difficulty = 2; Game::GetInstance().Reset("assets\\Levels\\level0.level"); };

	Difficulty3.SetPercentagePositionCentered({ 50, 46 });
	Difficulty3.SetString("Hard");
	Difficulty3.SetTextColor(sf::Color::White);
	Difficulty3.SetColor(sf::Color(128, 128, 128));
	Difficulty3.OnRelease += [&](UIElement*) {Game::GetInstance().Difficulty = 3; Game::GetInstance().Reset("assets\\Levels\\level0.level"); };

	Back.SetPercentagePositionCentered({ 50, 54 });
	Back.SetString("Back");
	Back.SetTextColor(sf::Color::White);
	Back.SetColor(sf::Color(128, 128, 128));
	Back.OnRelease += [&](UIElement*) { elements[0] = &HomeScreen; };
}