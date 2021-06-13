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

};