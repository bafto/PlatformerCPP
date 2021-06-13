#pragma once

#include "../UIState.h"
#include "../UIElements/UIButton.h"

class TestState : public UIState
{
public:
	TestState();
	virtual ~TestState();

	virtual void Initialize() override;

private:
	UIPanel panel;
	UIButton btn;

};