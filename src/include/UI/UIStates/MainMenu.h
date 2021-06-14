#pragma once

#include "../UIState.h"
#include "../UIElements/UIButton.h"

class MainMenu : public UIState
{
public:
	MainMenu();
	virtual ~MainMenu();

	virtual void Initialize() override;

private:
	UIPanel HomeScreen;
	UIText Headline;
	UIButton NewGame, LoadLevel, Quit;

	UIPanel ChooseDifficulty;
	UIText Headline2;
	UIButton Difficulty1, Difficulty2, Difficulty3, Back;

	sf::Sound btnHover, btnClick;
	sf::SoundBuffer btnHoverBuffer, btnClickBuffer;

};