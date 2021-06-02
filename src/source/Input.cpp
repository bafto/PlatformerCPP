#include "../include/Input.h"
#include <algorithm>

#pragma warning (disable : 26812)

Input::Input()
{
	Initialize();
}

void Input::Initialize()
{
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		keyboardState[i] = ButtonState();
		lastKeyboardState[i] = ButtonState();
	}
	for (int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		mouseState[i] = ButtonState();
		lastMouseState[i] = ButtonState();
	}
}

void Input::clear()
{
	std::copy(std::begin(keyboardState), std::end(keyboardState), std::begin(lastKeyboardState));
	std::copy(std::begin(mouseState), std::end(mouseState), std::begin(lastMouseState));
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
		keyboardState[i] = ButtonState();
	for (int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
		mouseState[i] = ButtonState();
}

void Input::update(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (!lastKeyboardState[event.key.code].down)
			keyboardState[event.key.code].pressed = true;
		keyboardState[event.key.code].down = true;
		break;
	case sf::Event::KeyReleased:
		keyboardState[event.key.code].released = true;
		break;
	case sf::Event::MouseButtonPressed:
		mouseState[event.mouseButton.button].pressed = true;
		mouseState[event.mouseButton.button].down = true;
		break;
	case sf::Event::MouseButtonReleased:
		mouseState[event.mouseButton.button].released = true;
		break;
	default:
		break;
	}
}

void Input::finishUpdate(sf::RenderWindow const* wnd)
{
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		if (!keyboardState[i].released && (lastKeyboardState[i].pressed || lastKeyboardState[i].held))
		{
			keyboardState[i].held = true;
			keyboardState[i].down = true;
		}
	}
	for (int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		if (!mouseState[i].released && (lastMouseState[i].pressed || lastMouseState[i].held))
		{
			mouseState[i].held = true;
			mouseState[i].down = true;
		}
	}

	mousePosWindow = sf::Mouse::getPosition(*wnd);
	mousePosWorld = wnd->mapPixelToCoords(mousePosWindow);
}

Input::ButtonState Input::KeyboardState(sf::Keyboard::Key key)
{
	return keyboardState[key];
}

Input::ButtonState Input::MouseState(sf::Mouse::Button button)
{
	return mouseState[button];
}

sf::Vector2i Input::MousePosWindow()
{
	return mousePosWindow;
}

sf::Vector2f Input::MousePosWorld()
{
	return mousePosWorld;
}