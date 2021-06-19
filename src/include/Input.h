#pragma once

#include "GeneralIncludes.h"

class Input
{
public:
	//state of a mouse or keyboard button
	struct ButtonState
	{
		bool pressed = false, released = false, held = false, down = false;
	};
public:
	//empty
	Input();

	//initialized mouse and keyboard states as empty
	void Initialize();

	//setup before updating (called before event loop)
	void clear();
	//update based on events (called inside event loop for every event)
	void update(sf::Event event);
	//finish the update (called after event loop)
	void finishUpdate(sf::RenderWindow const* wnd);

	//get Mouse or Keyboard states for btn or key
	ButtonState KeyboardState(sf::Keyboard::Key key);
	ButtonState MouseState(sf::Mouse::Button btn);

	sf::Vector2i MousePosWindow(); //mouse position relative to the window
	sf::Vector2f MousePosWorld(); //mouse position in the world

private:
	ButtonState keyboardState[sf::Keyboard::Key::KeyCount];
	ButtonState lastKeyboardState[sf::Keyboard::Key::KeyCount];
	ButtonState mouseState[sf::Mouse::Button::ButtonCount];
	ButtonState lastMouseState[sf::Mouse::Button::ButtonCount];

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosWorld;
};