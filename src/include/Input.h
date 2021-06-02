#pragma once

#include "GeneralIncludes.h"

class Input
{
public:
	struct ButtonState
	{
		bool pressed = false, released = false, held = false;
	};
public:
	Input();

	void Initialize();

	void clear();
	void update(sf::Event event);
	void finishUpdate(sf::RenderWindow const* wnd);

	ButtonState KeyboardState(sf::Keyboard::Key key);
	ButtonState MouseState(sf::Mouse::Button btn);

	sf::Vector2i MousePosWindow();
	sf::Vector2f MousePosWorld();

private:
	ButtonState keyboardState[sf::Keyboard::Key::KeyCount];
	ButtonState lastKeyboardState[sf::Keyboard::Key::KeyCount];
	ButtonState mouseState[sf::Mouse::Button::ButtonCount];
	ButtonState lastMouseState[sf::Mouse::Button::ButtonCount];

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosWorld;
};