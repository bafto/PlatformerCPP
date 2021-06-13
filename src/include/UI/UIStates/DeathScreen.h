#pragma once

#include "../UIState.h"
#include "../UIElements/UIButton.h"

class DeathScreen : public UIState
{
public:
	DeathScreen();
	virtual ~DeathScreen();

	virtual void Initialize() override;

private:
	UIPanel MainPanel;
	UIText Headline;
	UIButton Retry, MainMenu, Quit;

};