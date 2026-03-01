#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Event.hpp"
class InputImpl
{
public:

	inline static InputImpl& Get()
	{
		static InputImpl instance;
		return instance;
	}


	void UpdateKeyStates();
	void HandleKeyEvent(const sf::Event& event);


	bool GetKeyDown(sf::Keyboard::Scancode key);
	bool GetKeyUp(sf::Keyboard::Scancode key);
	bool GetKeyHeld(sf::Keyboard::Scancode key);

private:
	enum KeyState
	{
		NONE,
		DOWN,
		HELD,
		UP
	};

	KeyState m_keys[sf::Keyboard::ScancodeCount];
	InputImpl();

};