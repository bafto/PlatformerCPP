#pragma once

#include "../UIState.h"
#include "../UIElements/UIPanel.h"
#include "../UIElements/UIText.h"

class TestState : public UIState
{
public:
	TestState();
	virtual ~TestState();

private:
	UIPanel btn;
	UIText text;

};