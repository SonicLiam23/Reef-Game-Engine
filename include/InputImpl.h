#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "EngineAPI.h"
#include "Vector2.h"
#include "Input.h"
#include "Window.h"
class ENGINE_API InputImpl
{
public:

	struct ClickEvent
	{
		bool clicked;
		Math::Vector2f position;
	};

	inline static InputImpl& Get()
	{
		static InputImpl instance;
		return instance;
	}

	void init(Window* target);

	Window* GetWindow();
	void UpdateKeyStates();
	void HandleKeyEvent(const sf::Event& event);

	// API
	bool GetKeyDown(sf::Keyboard::Scancode key);
	bool GetKeyUp(sf::Keyboard::Scancode key);
	bool GetKeyHeld(sf::Keyboard::Scancode key);

	// mouse
	bool GetMouseButtonDown(sf::Mouse::Button button);
	bool GetMouseButtonUp(sf::Mouse::Button button);
	bool GetMouseButtonHeld(sf::Mouse::Button button);

private:
	enum KeyState
	{
		NONE,
		DOWN,
		HELD,
		UP
	};

	KeyState m_keys[sf::Keyboard::ScancodeCount];
	KeyState m_mouseButtons[sf::Mouse::ButtonCount];
	InputImpl();
	Window* m_window;
};