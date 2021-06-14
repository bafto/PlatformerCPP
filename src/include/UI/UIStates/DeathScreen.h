#pragma once

#include "../UIState.h"
#include "../UIElements/UIButton.h"
#include "../UIElements/UIImage.h"

class DeathScreen : public UIState
{
public:
	DeathScreen();
	virtual ~DeathScreen();

	virtual void Initialize() override;

public:
	UIImage MainPanel;

private:
	UIText Headline;
	UIButton Retry, MainMenu, Quit;

};