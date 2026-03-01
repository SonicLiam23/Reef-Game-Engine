#pragma once
#include "SFML/Window/Keyboard.hpp"

struct Input
{
	using Key = sf::Keyboard::Scancode;
	enum KeyType
	{
		SCANCODE,
		KEYCODE	
	};

	static bool GetKeyDown(Input::Key key);
	static bool GetKeyUp(Input::Key key);
	static bool GetKeyHeld(Input::Key key);
};