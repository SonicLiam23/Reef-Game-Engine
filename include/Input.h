#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "EngineAPI.h"
#include "Vector2.h"

struct ENGINE_API Input
{
	using Key = sf::Keyboard::Scancode;

	static bool GetKeyDown(Input::Key key);
	static bool GetKeyUp(Input::Key key);
	static bool GetKeyHeld(Input::Key key);

	static bool GetMouseButtonDown(sf::Mouse::Button button);
	static bool GetMouseButtonUp(sf::Mouse::Button button);
	static bool GetMouseButtonHeld(sf::Mouse::Button button);

	enum ClickType
	{
		NoClick,
		SingleClick,
		DoubleClick,
		Held,
		Up
	};

	struct ENGINE_API ClickEvent
	{
		ClickType clickType;
		Math::Vector2i position;
	};



	using MouseButton = sf::Mouse::Button;
	static ClickEvent GetMouseButtonInfo(MouseButton button = MouseButton::Left);
private:
	static sf::Time doubleClickThreshold;
	static sf::Clock lastClickTime[(int)sf::Mouse::Button::Count];

};